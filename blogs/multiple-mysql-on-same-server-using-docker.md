There are many situations where there is a require where you need to run multiple instances of MySQL on same machine.

Some situations are:

- test a new MySQL release while leaving an existing production setup undisturbed
- give different users access to different `mysqld` servers that they manage themselves

## Problem description
I have a machine having 5 products already setup. All products are using MySQL 5.5 as its default database. Now its time to upgrade all but one product to use MySQL 5.6. The table below shows the before and after version requirements of MySQL for various products. Looking at the table we find that all products except product C wants to use MySQL 5.6.

![multiple-mysql-requirement](https://user-images.githubusercontent.com/4745789/63223049-85472700-c1cd-11e9-88bb-5d3123b412ad.png)

Since all but one products require MySQL 5.6, so lets install it first and then we will work to figure out a way to install MySQL 5.5 as well.

## Installing MySQL 5.6
```bash
sudo apt-get update
sudo apt-get install mysql-server-5.6 mysql-server-core-5.6 mysql-client-5.6 mysql-client-core-5.6
```

At this point we have MySQL 5.6 listening at port `3306` (default port)

## Approach to solution
There are several approaches with which you can achieve multiple MySQL versions running in same machine. Some of them are

- Use binaries of specific version
- Build everything from MySQL source

## Issues in above approaches:
Evidently we can only have one version of MySQL setup on the machine using default installation procedure with `apt-get`. Hence if we try to install one version over other then it will replace the first version and will retain the second version. Hence we cannot have 2 versions of MySQL with default installation procedure.

Building everything from scratch involves a lot of complications at source level. In order to debug any issues that might arise, you should be aware what happens in various scripts/commands that you run. I did spend a day in building from the source but it eventually turned out to be complete waste of time, efforts and debugging.

## Docker to the rescue
If we had a container in which we have a MySQL 5.5 installed and if we can publish the container's port(s) to the host, then we can connect to container's MySQL just like a local database.

We can have all of the above with **Docker**. If you dont know what docker is, please read this official [What is Docker](https://www.docker.com/what-docker).

### Installing Docker
To install docker on your machine execute following command on your shell.

```bash
curl -sSL https://get.docker.com/ | sh
```

### Spin off MySQL 5.5 container
Execute following command and this will download MySQL 5.5 image and will spin off the container. This container will have MySQL 5.5 installed on port `3306`. But on host machine port `3310` will be forwarded.

```bash
sudo docker run --name mysql-55-container -p 127.0.0.1:3310:3306 \
     -e MYSQL_ROOT_PASSWORD=rootpassword -d mysql:5.5
```

_NOTE: Password for root user is rootpassword, you can change it to anything._

### Connect to MySQL 5.5
```bash
mysql -u root -p --host=127.0.0.1 --port=3310
```

### Connect to MySQL 5.6
```bash
mysql -u root -p
```

**And voila! you have both My SQL 5.5 and MySQL 5.6 installed and running on same machine.**

Now you can configure your application product C to use host `127.0.0.1` and port `3310` and thus you have products A, B, D and E running on MySQL 5.6 and product C running on MySQL 5.5.
