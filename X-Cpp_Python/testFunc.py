def say():
	print("hello python45asddasdas")
	return "yes"

def add(a,b):
	c=a+b
	print(f"{a}+{b}={c}")
	return c

class Person:
	def __init__(self,name,age):
		self.name=name
		self.age=age

	def foo(self):
		print(f"my name is {self.name}, my age is {self.age}")
