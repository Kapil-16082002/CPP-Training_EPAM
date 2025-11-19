#Definition
Object-oriented programming (OOP) is defined as a programming model (and not a specific language) built on the concept of objects,
 that helps in software or application designing.
 OOP focuses on the objects that developers want to manipulate rather than the logic required to manipulate them.

#Why OOps-
#1.Reusability-> Through inheritance, OOPs allow programmers to reuse code agin and again and extend the use of existing classes.
#2.Enhanced Security -> With encapsulation, critical or inernal data is hidden from outside interference, allowing only specific parts of the program 
to interact with the internal states of an object, improving security and reducing unintended side effects.
#3.Real world Mapping -> OOP mimics real world entities and have relationships by using objects,
For instance, an "Animal" class can have different derived classes like "Dog" and "Cat," having specific behaviors 
but following a general pattern.
#4.Abstraction -> OOPs hide complex implementation(un-necessary ) details  from user and shows only necessary details.


#Difference between OOps and Traditional(procedural) Programming-
#1.
OOP:
Promotes code reusability through inheritance and polymorphism. Classes can be extended, and objects can be reused across the program.
Procedural Programming:
Reusability is achieved through functions and procedures, but there is no inheritance mechanism. 

#2.
OOP:
Focuses on objects that represent(mimics) real-world entities.
Example: In a banking system, you may have objects like Account, Customer, each encapsulating its own data and functions.
Procedural Programming:
Focuses on procedures or functions that operate on data.
Example: In a banking system, functions like deposit(), withdraw() would operate on global or shared data structures.

#3.
Data is more secure as we have public, private, protected access modifiers.
Procedural Programming:
Data is typically stored in global variables or passed between functions and hence  less control over accessing of data, which can lead to unintended modifications or bugs.

	                OOP                                          	Procedural Programming
Main focus- 	    Objects (data + functions)	                       Functions and procedures
Approach-	        Bottom-up (design objects first)	               Top-down (design functions first)
Modularity-	        High (due to classes and objects)	               Moderate (via functions)
Data handling-	    Encapsulation (data is hidden)	                Data is passed between functions or shared globally
Code reusability-	High (through inheritance, polymorphism)	    Limited (reused via functions)
Security-	        Higher (data hidden within objects)             Lower (global data is more vulnerable)
Extensibility-	    Easier to extend and maintain	                Harder to modify without affecting the whole code
Best suited for-	Complex, large-scale systems	                Simple, linear tasks