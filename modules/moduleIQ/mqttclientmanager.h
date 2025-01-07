#ifndef MQTTCLIENTMANAGER_H
#define MQTTCLIENTMANAGER_H

#include <string>
#include <mqtt/async_client.h>
#include <mqtt/ssl_options.h>

class MqttClientManager {
public:
    // Static method to initialize the MQTT client
    static void initialize();

    // Static method to send messages asynchronously
    static void sendMessage(const std::string& message);

private:
    MqttClientManager(); // Private constructor
    ~MqttClientManager(); // Private destructor

    static MqttClientManager& instance();

    void connect();
    void publishMessage(const std::string& message);
    void configureSSL(mqtt::connect_options& conn_opts);

    // Static configuration parameters
    std::string  m_brokerAddress = "ssl://34.102.112.102:8883";          // Replace with your broker address
    std::string  m_clientId = "ScitonConnect";                           // Unique client ID
    std::string  m_topicName = "358643076067979/init";                   // MQTT topic
    std::string  m_clientKeyPassword = "";                              // Private key password (if needed)
    std::string  m_username = "358643076067979";                          // Private key password (if needed)
    std::string  m_password = "QR2196000701F118";                         // Private key password (if needed)

    std::string m_caCertPath = "/home/viraat/application/cacert.pem";   // CA certificate path
    std::string m_clientCertPath = "/home/viraat/application/cert.pem"; // Client certificate path
    std::string m_clientKeyPath = "/home/viraat/application/key.pem";   // Private key path

    mqtt::async_client m_asyncClient;
    const std::string m_topic;
};

#endif // MQTTCLIENTMANAGER_H
