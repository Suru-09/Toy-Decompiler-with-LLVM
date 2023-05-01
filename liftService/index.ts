import express from 'express';
import routes from './routes/routes';

const app = express();
app.use(express.json());

// Server PORT
const port = process.env.PORT || 5000;

app.use('/api', routes);

app.get('/', (req, res) => {
  res.status(200).json({ message: 'Hello, world!'});
});

// message to console the PORT for the server
app.listen(port, () => {
  console.log(`Server running on port ${port}`);
});