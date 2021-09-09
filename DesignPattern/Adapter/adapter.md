~~~mermaid
classDiagram
Client-->ClientInterface
ClientInterface<..Adapter
Adapter-->Service
    class ClientInterface{
		+method(data)
    }
    class Adapter{
    	-adaptee:Service
		+method(data)
    }
    class Service {
    ...
    +serviceMethod(specialData)
	}

~~~

