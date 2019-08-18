Majority of the traffic over the internet is HTTP Traffic. There is a HTTP Client which wants some data from HTTP Server, so it creates a HTTP Request Message in the protocol understandable by the server and sends it. Server reads the message, understands it, acts accordingly and replies back with HTTP Response.

This complete process is abstracted by the tools like [curl](https://curl.haxx.se/), requests libraries and utilities like [Postman](https://www.getpostman.com/). Instead of using these tools and utilities, we shall go by the hard way and see HTTP messages in action.

## The Webserver
For experimentation purpose let’s create a very basic webserver in [Python Flask framework](flask.pocoo.org) that exposes a trivial Hello World end point.

### Python webserver script
```python
from flask import Flask
app = Flask(__name__)

@app.route('/hello')
def hello():
    return "Hello, World!"

app.run(port=3000)
```

### Installing requirements
```bash
pip install flask
```

### Start the webserver
```bash
python hello.py
```

The server listens on port _3000_ . If you hit from the browser [http://localhost:3000/hello](http://localhost:3000/hello), you should see _Hello, World!_ rendered.

## The HTTP Request Message
A HTTP Client talks to HTTP Server via a common protocol that is understandable by the two parties. A sample HTTP request message looks something like

```bash
GET /hello.html HTTP/1.1
User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)
Host: www.sample-server.com
Accept-Language: en-us
Accept-Encoding: gzip, deflate
Connection: Keep-Alive
```

To understand more about HTTP Request messages, see references at the end of this article.

The HTTP Communication happens over a TCP Connection. So we create a TCP connection with the server and try to get response from it. To get a TCP connection I will use _netcat_.

## Netcat
_netcat_ is the utility that is used for just about anything under the sun involving TCP or UDP. It can open TCP connections, send UDP packets, listen on arbitrary TCP and UDP ports, do port scanning, and deal with both IPv4 and IPv6.

The webserver that was created above is listening on port _3000_ . Lets create a TCP Connection and connect to it using _netcat_.

```bash
netcat localhost 3000
```

The command along with creating a TCP connection, will also open a STDIN. Anything passed in that input stream will reach the server via the connection. Lets see what happens when we provide _This is a sample_ as input.

![bad-request](https://user-images.githubusercontent.com/4745789/63222752-65156900-c1c9-11e9-90ec-ed06362d5d83.jpg)

The input message given is not a valid HTTP message hence server responded with a status code of _400_ which is for [Bad Request](https://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html). And if you closely observe the server logs on flask application, you will see an entry of our last request.

Since the server is a HTTP Server, so it understands HTTP request. Let’s create one to hit our exposed API endpoint  _/hello_ .

The HTTP request message for this request looks something like this

```bash
GET /hello HTTP/1.1
```

And you should see output like this

![get-request](https://user-images.githubusercontent.com/4745789/63222756-78283900-c1c9-11e9-943a-60513ddbde86.jpg)

The HTTP Server understands the message sent from the client and it responded back as directed by the source code.

## Complex Requests and HTTP Request Messages

### GET method with query params and headers
Following method exposes an endpoint which accepts a [query parameter](https://en.wikipedia.org/wiki/Query_string) named _name_, and returns a response with _name_ in it.

```python
from flask import request

@app.route('/user')
def get_user():
    name = request.args.get('name')
    return "Requested for name = %s" % name
```

#### HTTP Request Message
Provide the HTTP request message below when STDIN opens up after you execute _netcat_ command and connect with the server.

```bash
GET /user?name=arpit HTTP/1.1
```

#### Output
![get-request-with-query-params](https://user-images.githubusercontent.com/4745789/63222764-87a78200-c1c9-11e9-83bc-edbd6cbfb32c.jpg)

### Basic POST Method example
Following method accepts form data via HTTP POST method and returns a dummy response with _username_ and _password_ in it.

```python
from flask import request

@app.route('/login', methods=['POST'])
def login():
    username = request.form.get('username')
    password = request.form.get('password')
    return "Login successful for %s:%s" % (username, password)
```

#### HTTP Request Message
Provide the HTTP request message below when STDIN opens up after you execute _netcat_ command and connect with the server.

```bash
POST /login HTTP/1.1
Content-Type: application/x-www-form-urlencoded
Content-Length: 32

username=arpit&password=welcome
```

#### Output
![post-request-with-form-data](https://user-images.githubusercontent.com/4745789/63222769-9c841580-c1c9-11e9-8593-7289b2a40a20.jpg)

### POST Method with JSON Request Body
Following method accepts JSON data that contains a field _id_ with integer value via HTTP POST method and returns a dummy response with _id_ in it.
```python
from flask import request

@app.route('/save', methods=['POST'])
def save_user():
    user_data = request.json
    return 'Saving user with id = %d' % (user_data.get('id'))
```

#### HTTP Request Message
Provide the HTTP request message below when STDIN opens up after you execute _netcat_ command and connect with the server.

```bash
POST /save HTTP/1.1
Content-Type: application/json
Content-Length: 30

{"id": 1092, "name": "Arpit"}
```

#### Output
![post-request-with-json-data](https://user-images.githubusercontent.com/4745789/63222775-ad348b80-c1c9-11e9-91ee-07933e37604d.jpg)

## Conclusion
The hard way to hit REST endpoints was not hard at all ;-) Stay curious and dive deep.

## References:
1. [HTTP/1.1: HTTP Message](https://www.w3.org/Protocols/rfc2616/rfc2616-sec4.html)
2. [HTTP Requests - Tutorialspoint](http://www.tutorialspoint.com/http/http_requests.htm)
3. [The TCP/IP Guide - HTTP Request Message Format](http://www.tcpipguide.com/free/t_HTTPRequestMessageFormat.htm)
4. [HTTP Status Codes](https://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html)
5. [Netcat man page](http://linux.die.net/man/1/nc)
6. [HTTP Methods](https://www.w3.org/Protocols/rfc2616/rfc2616-sec9.html)
