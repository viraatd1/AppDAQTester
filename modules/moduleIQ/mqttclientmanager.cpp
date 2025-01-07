#include "mqttclientmanager.h"
#include <iostream>
#include <memory> // Include this for std::shared_ptr
#include <fstream>
#include <stdexcept>
#include <iostream>

MqttClientManager::MqttClientManager() : m_asyncClient(m_brokerAddress, m_clientId), m_topic(m_topicName) {
    // No need to configure SSL options here directly.
}

MqttClientManager::~MqttClientManager() {
    try {
        m_asyncClient.disconnect()->wait();
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
        conn_opts.set_user_name(m_username);
        conn_opts.set_password(m_password);

        m_asyncClient.connect(conn_opts)->wait();
        std::cout << "Connected to the broker." << std::endl;
    } catch (const mqtt::exception& exc) {
        std::cerr << "Error connecting to broker: " << exc.what() << std::endl;
    }
}

void MqttClientManager::publishMessage(const std::string& message) {
    if (!m_asyncClient.is_connected()) {
        std::cerr << "Client is not connected. Cannot send message." << std::endl;
        return;
    }

    try {
        // Create the message using a shared pointer
        auto pubmsg = std::make_shared<mqtt::message>(m_topic, message, 1, false); // topic, payload, QoS, retained

        // Publish the message
        m_asyncClient.publish(pubmsg)->wait(); // Publish the message and wait for completion
        std::cout << "Message sent: " << message << std::endl;
    } catch (const mqtt::exception& exc) {
        std::cerr << "Error sending message: " << exc.what() << std::endl;
    }
}

void MqttClientManager::configureSSL(mqtt::connect_options& conn_opts) {

    // Check if certificate files exist
    auto fileExists = [](const std::string& path) -> bool {
        std::ifstream file(path);
        return file.good();
    };

    if (!fileExists(m_caCertPath)) {
        throw std::runtime_error("CA certificate file does not exist: " + std::string(m_caCertPath));
    }
    if (!fileExists(m_clientCertPath)) {
        throw std::runtime_error("Client certificate file does not exist: " + std::string(m_clientCertPath));
    }
    if (!fileExists(m_clientKeyPath)) {
        throw std::runtime_error("Client key file does not exist: " + std::string(m_clientKeyPath));
    }


    mqtt::ssl_options sslopts;
    sslopts.set_trust_store(m_caCertPath);
    sslopts.set_key_store(m_clientCertPath);
    sslopts.set_private_key(m_clientKeyPath);
    // If the private key is password-protected, uncomment the next line and set the password
    // sslopts.set_password(client_key_password);
    conn_opts.set_ssl(sslopts); // Set SSL options in connection options
}
