#include "mqttclientmanager.h"
#include <iostream>
#include <memory> // Include this for std::shared_ptr

//const char* MqttClientManager::broker_address = "ssl://your_broker_address"; // Set your broker address
//const char* MqttClientManager::client_id = "KConnect";
//const char* MqttClientManager::topic = "358643076067979/init";
//const char* MqttClientManager::ca_cert_path = "/application/auth/certs/cacert.pem";
//const char* MqttClientManager::client_cert_path = "/application/auth/certs/cert.pem";
//const char* MqttClientManager::client_key_path = "/application/auth/certs/key.pem";
//const char* MqttClientManager::client_key_password = "";

MqttClientManager::MqttClientManager() : client(broker_address, client_id), topic(topic_name) {
    // No need to configure SSL options here directly.
}

MqttClientManager::~MqttClientManager() {
    try {
        client.disconnect()->wait();
    } catch (const mqtt::exception& exc) {
        std::cerr << "Error during disconnect: " << exc.what() << std::endl;
    }
}

MqttClientManager& MqttClientManager::instance() {
    static MqttClientManager instance;
    return instance;
}

void MqttClientManager::initialize() {
    instance().connect();
}

void MqttClientManager::sendMessage(const std::string& message) {
    instance().publishMessage(message);
}

void MqttClientManager::connect() {
    try {
        mqtt::connect_options conn_opts;
        configureSSL(conn_opts); // Call the method to configure SSL options

        // Set username and password
        conn_opts.set_user_name(username);
        conn_opts.set_password(password);

        client.connect(conn_opts)->wait();
        std::cout << "Connected to the broker." << std::endl;
    } catch (const mqtt::exception& exc) {
        std::cerr << "Error connecting to broker: " << exc.what() << std::endl;
    }
}

void MqttClientManager::publishMessage(const std::string& message) {
    if (!client.is_connected()) {
        std::cerr << "Client is not connected. Cannot send message." << std::endl;
        return;
    }

    try {
        // Create the message using a shared pointer
        auto pubmsg = std::make_shared<mqtt::message>(topic, message, 1, false); // topic, payload, QoS, retained

        // Publish the message
        client.publish(pubmsg)->wait(); // Publish the message and wait for completion
        std::cout << "Message sent: " << message << std::endl;
    } catch (const mqtt::exception& exc) {
        std::cerr << "Error sending message: " << exc.what() << std::endl;
    }
}

void MqttClientManager::configureSSL(mqtt::connect_options& conn_opts) {
    mqtt::ssl_options sslopts;
    sslopts.set_trust_store(ca_cert_path);
    sslopts.set_key_store(client_cert_path);
    sslopts.set_private_key(client_key_path);
    // If the private key is password-protected, uncomment the next line and set the password
    // sslopts.set_password(client_key_password);
    conn_opts.set_ssl(sslopts); // Set SSL options in connection options
}
