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
    static constexpr const char* broker_address = "ssl://34.102.112.102:8883";          // Replace with your broker address
    static constexpr const char* client_id = "ScitonConnect";                           // Unique client ID
    static constexpr const char* topic_name = "358643076067979/init";                   // MQTT topic
    static constexpr const char* ca_cert_path = "/home/viraat/6_IQ/AppDAQTester/certs/cacert.pem";   // CA certificate path
    static constexpr const char* client_cert_path = "/home/viraat/6_IQ/AppDAQTester/certs/cert.pem"; // Client certificate path
    static constexpr const char* client_key_path = "/home/viraat/6_IQ/AppDAQTester/certs/key.pem";   // Private key path
    static constexpr const char* client_key_password = "";                              // Private key password (if needed)
    static constexpr const char* username = "358643076067979";                          // Private key password (if needed)
    static constexpr const char* password = "QR2196000701F118";                         // Private key password (if needed)

    mqtt::async_client client;
    const std::string topic;
};

#endif // MQTTCLIENTMANAGER_H
