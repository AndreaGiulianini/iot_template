# IoT MQTT Monitoring System

### 📋 Overview
This project implements a complete IoT monitoring system using MQTT, Elasticsearch, Logstash, and Kibana (ELK Stack), with ESP32 device support and remote access via ngrok.

### 🚀 Prerequisites
- Docker and Docker Compose installed
- Ngrok account
- ESP32 device (optional for hardware testing)
- Arduino IDE (if using ESP32)

### 📦 System Components
- **MQTT Broker**: Eclipse Mosquitto for message handling
- **Elasticsearch**: Database for data storage
- **Logstash**: Data processing pipeline
- **Kibana**: Data visualization and analysis
- **Web Interface**: Custom web interface
- **Ngrok**: Secure tunnel for remote access

### ⚙️ Installation and Launch

1. **Clone the repository**
   ```bash
   git clone [repository-url]
   cd [directory-name]
   ```

2. **Start the system**
   - On Linux:
     ```bash
     sh ./start.sh
     ```
   - On Windows:
     ```bash
     start.bat
     ```

3. **Verify services**
   - Kibana: http://localhost:5601
   - Elasticsearch: http://localhost:9200
   - Web Interface: http://localhost:3000
   - Ngrok Interface: http://localhost:4040

### 🔧 Kibana Configuration

1. Access Kibana (http://localhost:5601)
2. Navigate to Management > Stack Management > Index Patterns
3. Create a new index pattern:
   - Pattern name: `mqtt_logs*`
   - Timestamp field: `@timestamp`
4. Save the configuration

### 📡 System Testing

1. **Send MQTT messages via curl**
   ```bash
   curl -X POST https://[ngrok-domain]/publish \
   -H "Content-Type: application/json" \
   -d '{"message": "Test message"}'
   ```

2. **ESP32 Configuration**
   - Open the sketch file in Arduino IDE
   - Update WiFi credentials
   - Update MQTT broker address (from ngrok)
   - Upload sketch to device

### 🔍 Monitoring
- Use Kibana to view real-time messages
- Check Docker container logs for debugging
- Monitor ngrok connections from web interface

### 🛠️ Troubleshooting
1. **If services fail to start:**
   ```bash
   docker-compose down
   docker-compose up --build
   ```

2. **To reset volumes:**
   ```bash
   docker-compose down -v
   ```

### 📝 Note
The system uses Docker volumes for data persistence. All configurations are maintained in the respective configuration files in the project directory.