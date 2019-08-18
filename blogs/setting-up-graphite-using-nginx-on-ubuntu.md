Monitor your production systems and application analytics using Graphite. This article will help you setup these tools on Ubuntu 14.04 on a Nginx webserver with PostgreSQL as backend.

## What is what

### What is Graphite?
Graphite is an open source software that is used for monitoring any system. The monitored data is the numeric information that represents any performance metric. Graphite also as a renderer which renders this information as graphs.
[Official Documentation](http://graphite.readthedocs.org/en/1.0/overview.html)

### What is Nginx?
NGINX is a very fast Webserver, its faster than most web servers available in the market. The biggest advantage of Nginx is its concurrency (because of asynchronous nature). It can also act as

1. HTTP Cache
2. Reverse Proxy
3. Load Balancer

For more information visit [Nginx Wiki](https://en.wikipedia.org/wiki/Nginx)

# Installing Nginx

```bash
sudo apt-get install nginx nginx-extras
```

# Installing Graphite

## Graphite Ubuntu Package Installation

Install Graphite packages

```bash
sudo apt-get update
sudo apt-get install graphite-web graphite-carbon
```

**NOTE**: During the installation, you will be asked if during uninstallation of Graphite you also like to remove its files. Please select **NO** because anyways you can delete them manually. The files are kept in `/var/lib/graphite/whisper`.


## Install and Configure PostgreSQL Database
Graphite internally uses carbon and whisper database library for storing data. But the web application is a Django application which needs some data store for its own purpose. The default data store configured is SQLite3 database files. But this is not a full fledged database system hence we will use PostgreSQL.

Script to install database and libs used by Graphite to communicate with PostgreSQL

```bash
sudo apt-get install postgresql libpq-dev python-psycopg2
```

Once our PostgreSQL is installed we will create a user and a database

Login to PostgreSQL console

```bash
sudo -u postgres psql
```

Create a user *graphite* which will be used by Django to operate on our database.

```sql
$ CREATE USER graphite WITH PASSWORD 'mypassword';
```

Please make sure you select a secure password for your user.

Create a database *graphite* and give our new user *graphite* ownership of it.

```sql
$ CREATE DATABASE graphite WITH OWNER graphite;
```

Please verify is database is created or not by connection to it

```sql
$ \c graphite
```

If you can successfully connect to the database *graphite* then you are good to go to next step.

Exit from the PostgreSQL console

```sql
$ \q
```


## Configure Graphite Web Application

Now, as we have our PostgreSQL database and user ready to go we can now move to configuring the web application.

Open the Graphite web app configuration file:

```bash
sudo vim /etc/graphite/local_settings.py
```

Uncomment the *SECRET_KEY* and give a nice random value to it

```bash
SECRET_KEY = 'MY NICE RANDOM SALT'
```

Uncomment the *TIMEZONE* and set it to some appropriate value. I have set it to UTC, but you may choose any one you like

```bash
TIME_ZONE = 'UTC'
```

Uncomment the *USE_REMOTE_USER_AUTHENTICATION* and set tot to *True* so that remote user will be authenticated first before making any DB changes

```bash
USE_REMOTE_USER_AUTHENTICATION = True
```

Change the database dictionary definition:

```python
DATABASES = {
    'default': {
        'NAME': 'graphite',
        'ENGINE': 'django.db.backends.postgresql_psycopg2',
        'USER': 'graphite',
        'PASSWORD': 'mypassword',
        'HOST': '127.0.0.1',
        'PORT': ''
    }
}
```

Save and close this file.


## Sync the Database
Once your web application is configured, it is time to sync your database, create a super user and create the correct structure.

```bash
sudo graphite-manage syncdb
```

**NOTE**: It will ask you to create a superuser. Make sure you remember the credentials with which you create one. This user will be used to connect to Graphite application and be admin of it. Being admin you will change interface of Graphite and create graphs.


## Configure Carbon
Carbon is the Graphite storage backend.

Open the configuration file:

```bash
sudo vim /etc/default/graphite-carbon
```

Change value of *CARBON_CACHE_ENABLED* to *true*

```bash
CARBON_CACHE_ENABLED = true
```

This enables the carbon service to start at boot

Save and close the file.

Next, open the Carbon configuration file:

```bash
sudo vim /etc/carbon/carbon.conf
```

Set *ENABLE_LOGROTATION* to *True* to turn on log rotation

```bash
ENABLE_LOGROTATION = True
```

Save and close the file

## Configuring Storage Schemas
Now, open the storage schema file. This tells Carbon how long to store values and how detailed these values should be:

```bash
sudo vim /etc/carbon/storage-schemas.conf
```

Inside you will find entries like

```bash
[carbon]
pattern = ^carbon\.
retentions = 60:90d
```

which implies:
pattern that matches regular expression *^carbon\.* should retain the data with retention policy *60:90d* which is

* how often a metric is recorded: 60 seconds
* length of time to store those values: 90 days

For detail information on retention policy visit [here](http://graphite.readthedocs.org/en/latest/config-carbon.html#storage-schemas-conf)

Now we need to add our own entry. Let's take an example *test* i.e. we need to monitor data points and our data point entries will start with string *test*.

**NOTE**: This entry should be added before the default entry mentioned at the bottom of the file

```bash
[test]
pattern = ^test\.
retentions = 10s:10m,1m:1h
```

This will match any metrics beginning with "test.". It will store the data it collects two times, in varying detail.

The first archive definition *(1s:10m)* will create a data point every ten  seconds. It will store the values for only ten minutes.

The second archive *(1m:1h)* will create a data point every one minute. It will gather all of the data from the past minute (six points, since the previous archive creates a point every ten seconds) and aggregate it to create the point. By default, it does this by averaging the points, but we can adjust this later. It stores the data at this level of detail for one hour.

**This example is taken from this [link](https://www.digitalocean.com/community/tutorials/how-to-install-and-use-graphite-on-an-ubuntu-14-04-server)**

Save and close the file.

## Storage Aggregation Methods
This aggregation methods are used when we try to fetch data that is less detailed (In our previous example we saw 6 data points were aggregated to create 1 data point). Understanding aggregation is important is we want accurate metrics.

Default aggregation method is taking out mean of values which implies that all retention policies other than most detailed one will create data points by taking mean of all data points it received.

We can specify the aggregation configuration in file called *storage-aggregation.conf* . A sample file is already provided by Carbon, so you can simply copy-paste it for default behaviour.

```bash
sudo cp /usr/share/doc/graphite-carbon/examples/storage-aggregation.conf.example /etc/carbon/storage-aggregation.conf
```

You can view [official documentation](http://graphite.readthedocs.org/en/latest/config-carbon.html#storage-aggregation-conf) to understand it better.

Save and close the file.

Start the carbon service

```bash
sudo service carbon-cache start
```

## Setup uwsgi and init script
To install *uwsgi* globally you can run following command

```bash
sudo apt-get install python-dev
sudo pip install uwsgi
```

If *pip* is not installed in your system, you can run following command

```bash
sudo apt-get install python-pip
```

The entrance file for Django application is stored in directory */usr/share/graphite-web* and is by default named as *graphite.wsgi*. You should rename it to *graphite_wsgi.py*.

You can do this by executing following command

```bash
sudo cp /usr/share/graphite-web/graphite.wsgi /usr/share/graphite-web/graphite_wsgi.py
```

Create log files and socket files with appropriate permissions

```bash
sudo touch /var/run/graphite.sock
sudo chmod 777 /var/run/graphite.sock
sudo touch /var/log/graphite.log
sudo chmod 777 /var/log/graphite.log
```

Once you have *uwsgi* setup in your system its time to set up the init script which will make it easier to manage the service.

Create the following file

```bash
sudo vim /etc/init/uwsgi-graphite.conf
```

And put following content in it

```bash
# vim: syntax=upstart

env UWSGI_BIN=/usr/local/bin/uwsgi
env PYTHONPATH=/usr/share/graphite-web

expect fork
umask 0000

start on runlevel [2345]
stop on runlevel [!2345]

script
  exec $UWSGI_BIN --socket /var/run/graphite.sock --master --need-app \
  --catch-exceptions --reload-on-exception --pp $PYTHONPATH \
  -w graphite_wsgi:application --buffer-size 32768 -p 4 -O 2 >>/var/log/graphite.log 2>&1 &
end script
```

Now you can start the Graphite Web application service using following command

```bash
sudo service uwsgi-graphite start
```

But before you can see anything on browser you need to setup Nginx configuration

## Setup Nginx for Graphite

Let us first create all files and links

```bash
sudo touch /etc/nginx/sites-enabled/graphite
sudo ln -s /etc/nginx/sites-enabled/graphite /etc/nginx/sites-available/graphite

# Log files
sudo touch /var/log/nginx/graphite.access.log
sudo chmod 666 /var/log/nginx/graphite.access.log
sudo touch /var/log/nginx/graphite.error.log
sudo chmod 666 /var/log/nginx/graphite.error.log
```

Now we are ready for configuring Nginx server for Graphite

Open file */etc/nginx/sites-enabled/graphite* and put following content in it

```bash
sudo vim /etc/nginx/sites-enabled/graphite
```

Nginx configuration

```javascript
server {
  server_name graphite.yourservername.com;
  listen 80;

  rewrite ^(.*) https://$host$1 permanent;
}


server {
  server_name graphite.yourservername.com;


  listen 443 ssl spdy;


  access_log /var/log/nginx/graphite.access.log;
  error_log  /var/log/nginx/graphite.error.log;


  location = /robots.txt {
    echo "User-agent: *\nDisallow: /\n";
  }


  root /usr/share/graphite-web;

  location = /favicon.ico {
    return 204;
  }

  location /content {
    alias /usr/share/graphite-web/static;
    expires max;
  }

  location / {
    uwsgi_pass unix:/var/run/graphite.sock;
    include uwsgi_params;
  }

}
```

Now you can view a working Graphite on your server. Just hit *http://graphite.yourservername.com* from your favourite browser.


# See it working

Login to the system with credentials that you provided while creating the superuser.

Once you are logged in, you should see a screen like this.

[Landing page of Graphite](https://user-images.githubusercontent.com/4745789/63223185-5af66900-c1cf-11e9-9379-4de15f80ef93.png)

First we need to add data into the system. Remember we added a pattern matcher in Storage Schema, according to which any pattern that starts with **test.** will be recorded as our pattern. Lets add some random data

In order to add data we need to run following

```bash
echo "test.count 9 `date +%s`" | nc -q0 127.0.0.1 2003;
```

This will add one data metric of value 9 in system. Lets add some more data; this time wee loop through values

```bash
for i in 4 6 8 16 2; do echo "test.count $i `date +%s`" | nc -q0 127.0.0.1 2003; sleep 6; done
```


Now you should see something like this.

**I already had some data in the system, your graph will look a bit different but should be similar**

[test.count graph in Graphite](https://user-images.githubusercontent.com/4745789/63223192-795c6480-c1cf-11e9-9323-e5a91c767ec9.png)

This completes the setup of Graphite on your machine. Although the UI does not look good but when used along with Grafana, it gives a complete experience along with high level of customization and metric analytics.
