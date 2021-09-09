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

client want to use service's service method, but client's method can not match service's.

Concrete a Adapter inherit from Service Object, override service method which match client.
