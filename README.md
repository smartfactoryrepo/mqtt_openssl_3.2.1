# 🚀 MQTT Broker with OpenSSL 3.2.1 Support

This project is a customized version of the [Mosquitto MQTT broker](https://mosquitto.org/) enhanced to use **OpenSSL 3.2.1** for secure communication via TLS 🔒.

---

## 📁 Project Structure

```
mqtt_openssl_3.2.1/
├── src/             # Main source code for the broker
├── lib/             # External libraries
├── deps/            # Dependencies
├── include/         # Header files
├── doc/             # Documentation
├── examples/        # Example configs and usage
├── CMakeLists.txt   # Build configuration
└── LICENSE.txt      # License information
```

---

## ✅ Requirements

- 🧱 CMake
- 🧪 GCC or compatible C compiler
- 🔐 OpenSSL 3.2.1 installed on the system

---

## ⚙️ Build Instructions

1. **Clone the repository**  
   ```bash
   git clone https://github.com/smartfactoryrepo/mqtt_openssl_3.2.1.git
   cd mqtt_openssl_3.2.1
   ```

2. **Configure the project**  
   ```bash
   cmake .
   ```

3. **Compile the broker**  
   ```bash
   make
   ```

4. **Install (optional)**  
   ```bash
   sudo make install
   ```

---

## 🔧 Configuration

Edit your `mosquitto.conf` to enable TLS using OpenSSL 3.2.1:

```conf
listener 8883
cafile /path/to/ca.pem
certfile /path/to/server-cert.pem
keyfile /path/to/server-key.pem
tls_version tlsv1.3
```

> 📝 Make sure certificate and key files are accessible and correctly generated.

---

## ▶️ Run the Broker

To start the broker with your TLS-enabled config:

```bash
mosquitto -c /path/to/mosquitto.conf
```

---

## 🔍 Testing

Use Mosquitto clients to test the broker over TLS:

```bash
mosquitto_pub -h <broker_ip> -p 8883 \
  --cafile /path/to/ca.pem \
  --cert /path/to/client-cert.pem \
  --key /path/to/client-key.pem \
  -t "test/topic" -m "Hello, TLS!"
```

```bash
mosquitto_sub -h <broker_ip> -p 8883 \
  --cafile /path/to/ca.pem \
  --cert /path/to/client-cert.pem \
  --key /path/to/client-key.pem \
  -t "test/topic"
```

---

## 🤝 Contributing

Contributions are welcome! Feel free to open an issue or submit a pull request for improvements, bug fixes, or ideas 💡

---

## 📄 License

This project is based on the original Eclipse Mosquitto project and uses the same license.  
See [`LICENSE.txt`](./LICENSE.txt) for full details.
