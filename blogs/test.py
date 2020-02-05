import time

def my_decorator(fn):
  def wrapper_function(*args, **kwargs):
    start_time = time.time()
    value = fn(*args, **kwargs)
    print("the function execution took:", time.time() - start_time, "seconds")
    return value
  return wrapper_function

@my_decorator
def area(l, b):
  return l * b

area(3, 4)