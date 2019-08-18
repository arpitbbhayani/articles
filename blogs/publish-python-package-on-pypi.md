PyPI is the official Python Packages Index. Once you publish it on PyPI then it will can downloaded via a simple command `pip install <package>`. Life becomes simpler with this one line installation.

## 1: Create accounts
In order to submit your package on PyPI you need to have few accounts on PyPI websites. These account will enable you to maintain your packages and will provide you with an interface to edit your package.

Create your account on following sites:

* [PyPI Live](http://pypi.python.org/pypi?%3Aaction=register_form)
* [PyPI Test](http://testpypi.python.org/pypi?%3Aaction=register_form)


## 2: The `.pypirc` file
Now create a file in your home folder named `.pypirc`, which will be your configuration file that holds the authentication information of your PyPI accounts.

Create file `.pypirc` and put the contents shown below
```bash
vim ~/.pypirc
```

`.pypirc` file contents

```cpp
[distutils]
index-servers =
  pypi
  pypitest

[pypi]
repository: https://pypi.python.org/pypi
username: YOUR_USERNAME_HERE
password: YOUR_PASSWORD_HERE

[pypitest]
repository: https://testpypi.python.org/pypi
username: YOUR_USERNAME_HERE
password: YOUR_PASSWORD_HERE
```


You should replace `YOUR_USERNAME_HERE` and `YOUR_PASSWORD_HERE` with your username and password from PyPI sites that you just created.


## 3: The Python Package directory structure
* `source_dir` is a root directory that contains your python package
* `my_python_package` is your main python package that you want to publish


```cpp
source_dir/                 # the source directory
|-- my_python_package       # your package
|   |-- __init__.py
|   `-- FILES ....          # your package files
|-- README.md
|-- setup.cfg
|-- setup.py
```

Setup your directory structure as shown above, with appropriate changes, and host it on [github.com](http://github.com).

## 4: Release on github and get the download link
This step involves releasing your package on github. This will create a download link of your complete source. In order to release your github project, you need to carry on following steps:

1. Go to your project homepage on [github](http://github.com)
2. On top, you will see *Release link*. Click on it.
3. Click on *Draft a new relase*
4. Fill in all the details
	*  *Tag version* should be the version number of your package release
	*  *Release Title* can be anything you want.
5. Click *Publish release* at the bottom of the page
6. Now under *Releases* you can view all of your releases.
7. Copy the download link (tar.gz) and save it somewhere.


## 5: Editing files
Open the *setup.py* file and add following skeleton to it

```python
from distutils.core import setup

setup(
    name = 'my_python_package',
    packages = ['my_python_package'],
    version = 'version number',  # Ideally should be same as your github release tag varsion
    description = 'description',
    author = '',
    author_email = '',
    url = 'github package source url',
    download_url = 'download link you saved',
    keywords = ['tag1', 'tag2'],
    classifiers = [],
)
```

Open the *setup.cfg* file and add following skeleton to it

```python
[metadata]
description-file = README.md
```

Now push everything to github.


## 6: Publish the package
Execute following commands

```bash
python setup.py register -r pypitest
```

This command will try to register your package on PyPI test server. This makesures that everything you have setup is correct.

```bash
python setup.py sdist upload -r pypitest
```

This command will upload your package on test repository and now you should see your package on [PyPI Test](https://testpypi.python.org/pypi)

Now you are ready to publish your package on PyPI Live Server. Execute following commands

```bash
python setup.py register -r pypi
```

```bash
python setup.py sdist upload -r pypi
```

**Congratulations! You just published your python package on PyPI**

## References
1. [Official Documentation](http://wiki.python.org/moin/CheeseShopTutorial#Submitting_Packages_to_the_Package_Index)
