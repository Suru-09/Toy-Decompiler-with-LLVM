import express from 'express';
import routes from './routes/routes';

const bodyParser = require('body-parser');

const app = express();

// octet-stream for binary file
app.use(bodyParser.raw({type: 'application/octet-stream', limit : '2mb'}));
// json for everything else hopefully
app.use(express.json());

// Server PORT
const port: any = process.env.PORT || 29200;
const HOST = process.env.HOST || '0.0.0.0';
app.use('/api', routes);

app.get('/', (req, res) => {
  res.status(200).json({ message: 'Hello, world!'});
});

// message to console the PORT for the server
app.listen(port, HOST, () => {
  console.log(`Server running on port ${port}`);
});
