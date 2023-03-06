import express from 'express';

const app = express();

app.get('/', (req, res) => {
  res.send('Hello World!');
});


const port = process.env.PORT || 3000;

app.listen(3000, () => {
  console.log(`Server running on port ${port}`);
});


