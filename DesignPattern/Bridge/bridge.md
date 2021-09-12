~~~mermaid
classDiagram
	Client-->Adstraction
	Adstraction<|--Refined Abstraction
	Adstraction<|-->Implementation
	class Adstraction {
		-i:Implementation
		+feature1()
		+feature2()
	}
	class Implementation {
		+method1()
		+method2()
		+method3()
	}
	class Refined Abstraction {
		...
		+featureN()
	}
~~~

