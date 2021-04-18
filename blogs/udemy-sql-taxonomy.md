In this essay, we will model [taxonomy](https://en.wikipedia.org/wiki/Taxonomy) on top of a relational database, and as a specific example, we will try to build [Udemy's Taxonomy](https://www.udemy.com/). The primary focus of this essay is to understand how to design taxonomy on top of [SQL based relational DB](https://en.wikipedia.org/wiki/Relational_database), define and write queries that are computationally efficient along with deciding indexes on the designed tables.

In the process, we will also understand a very interesting SQL construct like Window Functions that helps us solve seemingly complex use-cases with a single SQL query.

# Udemy's Taxonomy

[Udemy's Taxonomy](https://www.udemy.com/) is very simple; it features top-level categories - like Software Engineering, Arts, and Business - each category has multiple sub-categories - like Programming Languages, Databases, Sketching - and each sub-category has niche topics like - Python, Javascript, MySQL, etc.

To keep things simpler, we restrain that one topic can be part of only one sub-category and one sub-category can belong to only one top-level category; and that makes the maximum levels in this taxonomy as `3`.

![https://user-images.githubusercontent.com/4745789/115139853-fcdbf200-a051-11eb-94f1-00382bd26db1.png](https://user-images.githubusercontent.com/4745789/115139853-fcdbf200-a051-11eb-94f1-00382bd26db1.png)

# Database Design

Out of our intuition, we can have one table for categories, one for holding sub-categories, and one for topics, and a bunch of [foreign keys](https://en.wikipedia.org/wiki/Foreign_key) that weaves them together. But is this the best we can come up with? A few issues with this design is

- all the 3 tables will have an identical schema
- if we were to introduce a new level, say `concept` that sits between sub-category and topic, we will have to create a new table to accommodate it, making this design cumbersome to future features and extensions.
- what if for a few topics we want it to be a child of a category, leaving out sub-categories altogether; handling this with this design will be very tricky.

So, a better design is to have a single table called `topics` that holds categories, sub-categories, and topics differentiated with a column called `type` that helps us identify what is it. The schema of this table `topics` would be

![https://user-images.githubusercontent.com/4745789/115140362-8260a180-a054-11eb-8820-2a830dcc025e.png](https://user-images.githubusercontent.com/4745789/115140362-8260a180-a054-11eb-8820-2a830dcc025e.png)

Now that we have the table `topics` ready, we see how the following two topics are stored

- Software Engineering > Programming Languages > Python
- Software Engineering > Programming Languages > Javascript

![https://user-images.githubusercontent.com/4745789/115140389-b340d680-a054-11eb-8a6d-b39a9f15fde8.png](https://user-images.githubusercontent.com/4745789/115140389-b340d680-a054-11eb-8a6d-b39a9f15fde8.png)

# Indexes on `topics`

Picking the right set of indexes is one of the most critical decisions that you will be taking while designing this system. A good set of indexes boosts the overall performance of the system, while poor ones or missing ones will put your database under terrible load, especially at scale.

But how do we pick which indexes do we want on `topics`? The answer here is very simple, it depends on the kind of queries we have to support. So, let's list down queries that we will need and then determine indexes to make them efficient.

## Get topic by ID

The most common query that we have to support is getting a topic by its `id` and this is very well facilitated by making `id` as a [primary key](https://en.wikipedia.org/wiki/Primary_key) of the table.

```sql
SELECT * FROM topics WHERE id = 531;
```

## Get the topic path

Getting a topic path is an interesting use case. While rendering any category, sub-category, or topic page we would need to render breadcrumbs that hold the path to it. For example, for Python's page, we will need to render a path like

```python
Software Engineering > Programming Languages > Python
```

This path helps users explore and discover new categories, sub-categories, or topics. So, using our current schema, how could we compute the topic path, given a topic id.

Doing it on the application side is the first approach that comes to mind but it is a poor one because we would be making `n` selects for `n` levels. So without constraints, we will be making `3` selects to compute the topic path. The application pseudocode would look something like this

```python
def get_topicpath(topic_id):
    path = []

    topic = get_topic_by_id(topic_id)
    path.append(topic)

    while topic.parent_id:
        topic = get_topic_by_id(topic.parent_id)
        path.append(topic)
    
    return path
```

We can do a lot better than this. Since we know that the hierarchy has at max 3 levels, we can just do this in one SQL query with some edge case handling on the application side.

The SQL query would have to join `3` instances of the `topics` table, each one handling one level in the hierarchy. The SQL query looks that fetches `id` and `name` of the topics in the topic path is as follows

```sql
SELECT topics_level1.id, topics_level1.name,
       topics_level2.id, topics_level2.name,
       topics_level3.id, topics_level3.name

FROM topics AS topics_level3
    LEFT JOIN topics AS topics_level2
        ON topics_level2.id = topics_level3.parent_id
    LEFT JOIN topics AS topics_level1
        ON topics_level1.id = topics_level2.parent_id

WHERE topics_level3.id = 610;
```

In the SQL query above we fetch the topic path for topic id `610`. We join table `topics` twice each handling a distinct level. Since we are using JOIN, if a parent is `NULL` and the join param does not match anything then it results in `NULL` during selects. This comes in very handy when we compute the topic path for anything other than `topic`.

If the topic with `610` id is of type `topic` then

- `topics_level1.id`, `topics_level1.name` will be category
- `topics_level2.id`, `topics_level2.name` will be sub-category
- `topics_level3.id`, `topics_level3.name` will be topic

If the topic with `610` id is of type `sub-category` then

- `topics_level1.id`, `topics_level1.name` will be `NULL`
- `topics_level2.id`, `topics_level2.name` will be category
- `topics_level3.id`, `topics_level3.name` will be sub-category

If the topic with `610` id is of type `category` then

- `topics_level1.id`, `topics_level1.name` will be `NULL`
- `topics_level2.id`, `topics_level2.name` will be `NULL`
- `topics_level3.id`, `topics_level3.name` will be category

So, in the application code, we still access all the selected columns but we create the topic path considering the `NULL` values of the selected columns.

To support this query, our table only requires Primary Key on `id` and Foreign Key on `parent_id`.

## Get all the children of a category or a sub-category

Getting all the children of a category or a sub-category will be heavily used to drive the "Browse and Explore" page, where users would want to drill down and explore the kind of topics Udemy is covering. SQL Query for this has to support pagination and will be required to output all children for a given parent.

```sql
SELECT * FROM topics WHERE parent_id = 123 ORDER BY score DESC;
```

The SQL query above fetches all the child topics of a given parent topic with `id` = `123`. The child-topics have to be ordered by `score` because we would want the most popular topic to be returned first. For this query to be efficient we create a [composite index](https://en.wikipedia.org/wiki/Composite_index_(database)) on `(parent_id, score)`. 

## Get category hierarchy

Udemy, on its home page, puts out all the categories under a dropdown menu enabling users to explore courses. One peculiar behavior of this is it renders all categories and top `k` sub-categories within it. Once we hover upon a sub-category it makes a network call to fetch top topics within that. It means we will need to fetch all categories and top `k` sub-categories from the entire `topics` table.

Although it looks very complicated at first, it is very easy to do with a single SQL query.

```sql
SELECT t1_id, t1_name, t2_id, t2_name, t2_score
FROM (
    SELECT topics1.id AS t1_id, topics1.name AS t1_name,
           topics2.id AS t2_id, topics2.name AS t2_name,
           ROW_NUMBER() OVER (PARTITION BY topics1.id) row_num

    FROM topics AS topics1
        LEFT JOIN topics AS topics2 ON topics1.id = topics2.parent_id

    WHERE topics1.type = 1 and topics2.type = 2

    ORDER BY topics1.score DESC, topics2.score DESC

) t
WHERE row_num <= 10;
```

Above SQL query picks all categories and top `10` sub-categories from each category and returns it as part of `SELECT`. To do this we use a very interesting SQL construct called Window Functions, specifically [`ROW_NUMBER`](https://dev.mysql.com/doc/refman/8.0/en/window-function-descriptions.html#function_row-number) and `PARTITION BY`.

We perform the usual join on `topics` once where the left operand is categories and the right one is a sub-category. We then partition this join by `id` of categories and then compute `ROW_NUMBER` for sub-categories within it.

The row numbers are computed for each partition separately so it goes as `1, 2, 3, ..., n` for `n` rows in it. We then apply a simple `WHERE` clause check on this row number to be `<= k` which then typically allows the first `k` row within each partition i.e. sub-categories within every category.

Note: to get "top" `k` sub-categories we just apply for an additional `ORDER BY` on `score` that sorts the sub-categories ensuring top sub-categories are fetched first. This way the first `k` rows we filter out from the partition are essentially the top sub-categories within the category.

To make this SQL query efficient we would need a foreign key on `parent_id` and an index on `score` to make `ORDER BY` efficient.

## Summary of indexes we need on `topics`

- Primary Key on `id`
- Foreign Key on `parents_id`
- Index on `type`
- Composite Index on `(parent_id, score)`

# Explore more

Although we covered quite a bit it will be a fun exercise to

- explore [Nested Set Model](https://en.wikipedia.org/wiki/Nested_set_model) to design Taxonomy on relational databases
- explore how DB engines behave when there are no indexes
- find if there could be a better alternative to paginate results apart from `LIMIT/OFFSET`

So this way, we can design Taxonomy on top of SQL-based relational databases like MySQL, Postgres, etc. We also saw determined the indexes we would need to make taxonomy efficient.

# References

- [Window Functions - MySQL](https://dev.mysql.com/doc/refman/8.0/en/window-function-descriptions.html)
- [Partitioning Types - MySQL](https://dev.mysql.com/doc/mysql-partitioning-excerpt/8.0/en/partitioning-types.html)
