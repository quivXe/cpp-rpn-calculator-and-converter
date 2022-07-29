# cpp-rpn-calculator-and-converter
written in C++ calculator, that works on reverse polish notation (rpn). Automatically convert infix notation (normal) to rpn and gives result.

Code has 2 usable functions:
 - double calculate_rpn(string operation): returns result and accept string that is in rpn
 - string convert_ifn_to_rpn(string operation): returns string ready to use in calculate_rpn()
 
 Each number and symbol must have space between to seperate it from rest. Dont put space at the end of operation, cuz program automatically detects whether operation is in rpn or ifn based on last char.
