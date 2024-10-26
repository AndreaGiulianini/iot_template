import Fastify from 'fastify'
import mqtt from 'mqtt';

const fastify = Fastify({
    logger: true
  })
  
const mqttClient = mqtt.connect('mqtt://mqtt:1883');

let lastMessage = '';

mqttClient.on('connect', () => {
  console.log('Connected to MQTT broker');
  mqttClient.subscribe('my-channel', (err) => {
    if (err) {
      console.error('Failed to subscribe to topic:', err);
    }
  });
});

mqttClient.on('message', (topic, message) => {
  console.log(`Message received on ${topic}: ${message.toString()}`);
  lastMessage = message.toString();
});

// Endpoint for publishing messages
fastify.post('/publish', async (request, reply) => {
  const { message } = request.body;
  mqttClient.publish('my-channel', message);
  reply.send({ status: 'Message published', message });
});

// Endpoint for getting the last message
fastify.get('/last-message', async (request, reply) => {
  reply.send({ message: lastMessage });
});

const start = async () => {
  try {
    await fastify.listen({ port: 3000, host: '0.0.0.0' });
    console.log('Server executing on http://localhost:3000');
  } catch (err) {
    fastify.log.error(err);
    process.exit(1);
  }
};

start();