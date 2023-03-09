import express from 'express';
import routes from './routes/routes';

const app = express();
app.use(express.json());

// Server PORT
const port = process.env.PORT || 3000;

app.use('/api', routes);

// message to console the PORT for the server
app.listen(3000, () => {
  console.log(`Server running on port ${port}`);
});