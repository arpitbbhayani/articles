Monitor your production systems and application analytics using Grafana and Graphite. This article will help you setup these tools on Ubuntu 14.04 on a Nginx webserver with PostgreSQL as backend.

**Before starting following this setup, please go through my previous post on [Deploy Graphite and Nginx on an Ubuntu 14.04 server](/blogs/setting-up-graphite-using-nginx-on-ubuntu)**

## What is what

### What is Grafana?
Grafana is a tool for visualising time-series data for various application analytics. It is a great tool when used in combination with Graphite. It gives us flexibility of creating dashboards and share them with teams.
[Grafana Official](http://grafana.org/)


# Installing Graphite

To install Graphite please follow this tutorial on [Deploy Graphite and Nginx on an Ubuntu 14.04 server](/blogs/setting-up-graphite-using-nginx-on-ubuntu).


# Installing Grafana

## Install Ubuntu Packages

Executing following commands will install Grafana on your machine

```bash
echo 'deb https://packagecloud.io/grafana/stable/debian/ wheezy main' |  sudo tee -a /etc/apt/sources.list
curl https://packagecloud.io/gpg.key | sudo apt-key add -
sudo apt-get update
sudo apt-get install grafana
```


## Create a database for Grafana

Just as we created the database for Graphite on PostgreSQL, we will create a database for Grafana as well. Create a database **grafana** and give user **graphite** (the user having access to Graphite database) ownership of it.

```sql
$ CREATE DATABASE grafana WITH OWNER graphite;
```

## Configure Grafana

Edit the Grafana configuration file

```bash
sudo vim /etc/grafana/grafana.ini
```

The settings should be something like this

```bash
[database]
type = postgres
host = 127.0.0.1:5432
name = grafana
user = graphite
password = mypassword

[server]
protocol = http
http_addr = 127.0.0.1
http_port = 3000
domain = grafana.yourservername.com
enforce_domain = true
root_url = %(protocol)s://%(domain)s/

[security]
admin_user = admin
admin_password = your_secure_password
secret_key = your_random_secret_salt
```

Once your configuration is done, you can start Grafana Server by running

```bash
sudo service grafana-server start
```

The log files are located at **/var/log/grafana/grafana.log**

If everything goes well the log file should have content

```bash
$ tail /var/log/grafana/grafana.log

[0]: default.paths.data=/var/lib/grafana
[1]: default.paths.logs=/var/log/grafana
Paths:
  home: /usr/share/grafana
  data: /var/lib/grafana
  logs: /var/log/grafana

2015/12/16 06:37:15 [I] Database: postgres
2015/12/16 06:37:15 [I] Migrator: Starting DB migration
2015/12/16 06:37:15 [I] Listen: http://127.0.0.1:3000
```


## Setup Nginx for Graphite

Let us first create all files and links

```bash
sudo touch /etc/nginx/sites-enabled/grafana
sudo ln -s /etc/nginx/sites-enabled/grafana /etc/nginx/sites-available/grafana

# Log files
sudo touch /var/log/nginx/grafana.access.log
sudo chmod 666 /var/log/nginx/grafana.access.log
sudo touch /var/log/nginx/grafana.error.log
sudo chmod 666 /var/log/nginx/grafana.error.log
```

Now we are ready for configuring Nginx server for Grafana

Open file */etc/nginx/sites-enabled/grafana* and put following content in it

```bash
sudo vim /etc/nginx/sites-enabled/grafana
```

Nginx configuration

```javascript
server {
  server_name grafana.yourservername.com;
  listen 80;

  rewrite ^(.*) https://$host$1 permanent;
}


server {
  server_name grafana.yourservername.com;


  listen 443 ssl spdy;


  access_log /var/log/nginx/grafana.access.log;
  error_log  /var/log/nginx/grafana.error.log;


  location = /robots.txt {
    echo "User-agent: *\nDisallow: /\n";
  }

  location / {
    proxy_pass         http://localhost:3000;
    proxy_set_header   Host $host;
  }

}
```

Now you can view a working Grafana on your server. Just hit *http://grafana.yourservername.com* from your favourite browser.


# See it working

Once you open the Grafana page, you will see a page something like this.

![Grafana 1](https://user-images.githubusercontent.com/4745789/63223325-487d2f00-c1d1-11e9-90b2-98cc5826b3a9.png)

Log in to the system with default credentials

* username: admin
* password: admin

Once you are logged in, you should see a screen like this.

![Grafana 2](https://user-images.githubusercontent.com/4745789/63223333-664a9400-c1d1-11e9-8a67-5b83d94d198b.png)

Before you see any analytics information here, you should add your data source. The data source you will add will be Graphite that was setup earlier.

Goto **Data Source** -> **Add New**

Make following changes:

* Name: **graphite**
* URL: **graphite.yourservername.com**

You should test your connection before adding any dashboard.

![Grafana 3](https://user-images.githubusercontent.com/4745789/63223336-71052900-c1d1-11e9-8d87-cdc739008770.png)

Once the connection is successful, now we are ready to add our first dashboard. Go to home page and goto **New Dashboard** -> **New**

Once that is done, you can add panels to it. To add graphs in panels click on **Green Button** -> **Add Panel** -> **Graph**. At the botton you will see metrics in which select *test* and *count*. Then you will see screen something like this.

![Grafana 4](https://user-images.githubusercontent.com/4745789/63223338-79f5fa80-c1d1-11e9-80cd-739bc6f0f8b7.png)

## More Information
Please follow the below links in order to know more about Grafana and its amazing customizations.

* [Grafana Documentation](http://docs.grafana.org/)
* [Adding Graphite to Grafana Official](http://docs.grafana.org/datasources/graphite/)
* [Adding HuBot to Grafana](http://docs.grafana.org/tutorials/hubot_howto/)
