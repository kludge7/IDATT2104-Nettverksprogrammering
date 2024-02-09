java -Djavax.net.ssl.keyStore=serverkeystore.jks -Djavax.net.ssl.keyStorePassword=password JavaSSLServer

java -Djavax.net.ssl.trustStore=clienttruststore.jks -Djavax.net.ssl.trustStorePassword=password JavaSSLClient
