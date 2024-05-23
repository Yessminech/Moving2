1. Code Layout
Explanation: Imports should be on separate lines; function definition should have the colon followed by a new line.
Good Example:

```
import os
import sys

def my_function():
    pass
```

Bad Example:

```
import os, sys
def my_function(): pass
```


2. Indentation
Explanation: Use four spaces per indentation level.
Good Example:

```
if x == 4:
    print(x)
```

Bad Example:

```
if x == 4:
print(x)
```

3. Maximum Line Length
Explanation: Limit all lines to a maximum of 79 characters.
Good Example:

```
def long_function_name(var_one, var_two, var_three, 
                       var_four):
    print(var_one)
```

Bad Example:

```
def long_function_name(var_one, var_two, var_three, var_four): print(var_one)
```

4. Blank Lines
Explanation: Surround top-level function and class definitions with two blank lines.
Good Example:

```
class MyClass:
    pass


def my_function():
    pass
```

Bad Example:
```
class MyClass:
    pass
def my_function():
    pass
```



5. Source File Encoding
Explanation: Specify UTF-8 encoding.
Good Example:
```
# -*- coding: utf-8 -*-
```

6. Imports
Explanation: Each import should be on a separate line.
Good Example:
```
import os
import sys
from subprocess import Popen, PIPE
```

Bad Example:
```
import sys, os
from subprocess import *
```

7. Module Level Dunder Names
Explanation: Use dunder names for module-level “magic” objects and attributes.
Good Example:

```
__all__ = ['a', 'b', 'c']
```

Bad Example:
```
all = ['a', 'b', 'c']
```

8. String Quotes
Explanation: Use consistent string quote style.
Good Example:

```
my_string = "Hello, world!"
```

Bad Example:
```
my_string = 'Hello, world!'
```

9. Whitespace in Expressions and Statements
Explanation: Avoid extraneous whitespace.
Good Example:
```
a = b + c
```

Bad Example:
```
a=b+c
```

10. Naming Conventions
Explanation: Use CapWords for class names and lower_case_with_underscores for functions.
Good Example:
```
class MyClass:
    pass

def my_function():
    pass
```

Bad Example:
```
class myclass:
    pass

def MyFunction():
    pass
```

11. Comments
Explanation: Use complete sentences for comments.
Good Example:
```
def my_function():
    # This is a single line comment.
    pass
```

Bad Example:
```
def my_function():
    # Comment
    pass
```

12. Docstrings
Explanation: Functions and classes should include docstrings.
Good Example:
```
def my_function():
    """
    This is a docstring example.
    Explains the function's purpose and usage.
    """
    pass
```

13. Comparisons
Explanation: Use is and is not for identity comparisons.
Good Example:
```
if foo is not None:
    pass
```

Bad Example:
```
if foo != None:
    pass
```

14. Blank Lines Between Functions and Classes
Explanation: Two blank lines between top-level functions and class definitions.
Good Example:
```
def function_one():
    pass


def function_two():
    pass
```

Bad Example:
```
def function_one():
    pass
def function_two():
    pass
```

15. Line Breaks with Parentheses
Explanation: Use parentheses for line continuation.
Good Example:
```
foo = long_function_name(var_one, var_two,
                         var_three, var_four)
```
Bad Example:
```
foo = long_function_name(var_one, var_two, \
                         var_three, var_four)
```

16. Break Before Binary Operator
Explanation: Break after a binary operator.
Good Example:
```
total = (first_variable
         + second_variable
         - third_variable)
```
Bad Example:
```
total = (first_variable +
         second_variable -
         third_variable)
```

17. Avoid Unnecessary Parentheses
Explanation: Avoid redundant parentheses.
Good Example:
```
a = 1 + 2
```

Bad Example:
```
a = (1 + 2)
```

18. Trailing Commas
Explanation: Include trailing commas in multi-line constructs.
Good Example:
```
my_list = [
    1,
    2,
    3,
]
```
Bad Example:
```
my_list = [
    1,
    2,
    3
]
```

19. Conditional Statements
Explanation: Place constants on the left in comparisons to prevent assignment errors.
Good Example:
```
if 42 == value:
    pass
```
Bad Example:
```
if value == 42:
    pass
```

20. Exception Handling
Explanation: Use specific exceptions.
Good Example:
```
try:
    value = my_dict['key']
except KeyError:
    value = 'default'
For more detailed information, please refer to the original article.
```

Bad Example:
```
try:
    value = my_dict['key']
except:
    value = 'default'
```
