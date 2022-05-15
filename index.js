const mqtt = require("mqtt");

const host = "localhost";
const port = "1883";
const clientId = `mqtt_${Math.random().toString(16).slice(3)}`;

const connectUrl = `mqtt://${host}:${port}`;
const topic = "teste";

const client = mqtt.connect(connectUrl, {
  clientId,
  clean: true,
  connectTimeout: 4000,
  //username: 'emqx',
  //password: 'public',
  reconnectPeriod: 1000,
});


async function connect(){
    if(global.connection && global.connection.state !== 'disconnected')
        return global.connection;
 
    const mysql = require("mysql2/promise");
    const connection = await mysql.createConnection("mysql://root:fabio123@localhost:3306/topicos");
    console.log("Conectou no MySQL!");
    global.connection = connection;
    connection.query('CREATE TABLE IF NOT EXISTS '+topic+'(id INT AUTO_INCREMENT PRIMARY KEY, message VARCHAR(255), created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP)');
    return connection;
}

async function insert(topic, payload){
    const conn = await connect();
    let sql = 'INSERT INTO '+topic+'(message) VALUES (?);';
    let value = payload.toString()
    return await conn.query(sql, value);
}


client.on("connect", () => {
  console.log("Connected");

  client.subscribe([topic], () => {
    console.log(`Subscribe to topic '${topic}'`);
  });
  /*
  client.publish(topic, 'nodejs mqtt test', { qos: 0, retain: false }, (error) => {
    if (error) {
      console.error(error)
    }
  })
  */
});
client.on("message",async (topic, payload) => {
  let now = new Date();
  console.log("Received Message:", topic, payload.toString(), now);
  
  
  await insert(topic, payload);
});
