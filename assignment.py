#!/usr/bin/python

"""
Finish the implementation of print_UTF8_as_numbers
"""

def eprint(string):
    """ Prints given string to stderr """

    #TODO Implementation

import sys

def print_UTF8_as_numbers(input_bytes):
    """
    Gets bytes which represents UTF8 string. 
    For each character prints its Unicode value.
    Every value should be on a separate line
    """

    #TODO Implementation

content = sys.stdin.buffer.read()
eprint(f"Passing {len(content)} bytes as {type(content)} to your function")
print_UTF8_as_numbers(content)
