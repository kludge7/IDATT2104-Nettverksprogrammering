# Use an official OpenJDK image with Maven included
FROM maven:3.8.1-openjdk-11-slim

# Set the working directory to /app
WORKDIR /app

# Install build tools
RUN apt-get update && apt-get install -y build-essential

# Copy the Maven project file
COPY pom.xml .

# Build all the dependencies in preparation to go offline.
# This is a separate step so it will cache.
RUN mvn dependency:go-offline -B

# Copy the project source
COPY src src

# Package the application
RUN mvn package -DskipTests

# Make port 8080 available to the world outside this container
EXPOSE 8080

# Run the application
CMD ["java", "-jar", "target/compiler-0.0.1-SNAPSHOT.jar"]
