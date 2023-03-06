import express, {Request, Response} from 'express';
import {spawn} from 'child_process';
import multer from 'multer';
import fs from 'fs';

const app = express();

// Middleware to parse JSON body
const upload = multer({
    storage: multer.diskStorage({
      destination: (req, file, cb) => {
        cb(null, 'uploads/'); // save files to the 'uploads' directory
      },
      filename: (req, file, cb) => {
        cb(null, file.originalname); // use original filename
      },
    }),
});

/************************************************************/
/*  ALL ROUTES FOR REST SERVER (GET & POST for now)         */
/************************************************************/

// DEFAULT ROUTE
app.get('/', (req, res) => {
    res.send('Hello World!');
  });

// POST FOR BINARY FILE
app.post('/api/upload', upload.single('file'), (req: Request, res: Response) => {
    if (!req.file) {
      return res.status(400).json({ message: 'No file uploaded' });
    }

    res.status(200).json({ message: `File ${req.file} been uploaded successfully` });
});

// ASK IF BINARY FILE WAS UPLOADED
app.get('/api/exist', (req: Request, res: Response) => {
    if(!req.file) {
        return res.status(400).json({ message: 'Key called <file> missing from GET request!' });
    }

    const filePath: string = "uploads/" + req.file;
    if(!fs.existsSync(filePath)) {
        return res.status(400).json({ message: `File ${req.file} does not exist` });
    }
    else { // file exists
        return res.status(200).json({ message: `File ${req.file} exists` });
    }
});

// IF BINARY FILE WAS UPLOADED, START LIFTING IT
app.post('/api/lift-executable', (req: Request, res: Response) => {
    if(!req.file) {
        return res.status(400).json({ message: 'Key called <file> missing from GET request!' });
    }
  
    // Spawn child process to run executable
    const args: string[] = [`${req.file}`, "--print-after-all"];
    const childProcess = spawn('binary/retdec-decompiler', args);
  
    // Listen for child process exit event
    childProcess.on('exit', (code: number) => {
      // Send response when child process has finished
      res.status(200).json({ message: `Execution finished with code ${code}` });
    });
  
    // Send response immediately to notify user that server is running the executable
    res.status(200).json({ message: 'Executing...' });
});

// ASK IF IR FILE HAS BEEN CREATED
app.get('/api/ir-exist', (req: Request, res: Response) => {
    if(!req.file) {
        return res.status(400).json({ message: 'Key called <file> missing from GET request!' });
    }

    const filePath: string = "gen/" + req.file;
    if(!fs.existsSync(filePath)) {
        return res.status(400).json({ message: `File ${req.file} does not exist` });
    }
    else { // file exists
        return res.status(200).json({ message: `File ${req.file} exists` });
    }
});

// GET IR FILE
app.get('/api/ir', (req: Request, res: Response) => {
    if(!req.file) { // if no file was uploaded
        return res.status(400).json({ message: 'Key called <file> missing from GET request!' });
    }

    const filePath: string = "gen/" + req.file;
    const fileContents = fs.readFileSync(filePath, 'utf8');
    return res.status(200).json({ message: fileContents });
});

// Server PORT
const port = process.env.PORT || 3000;

// message to console the PORT for the server
app.listen(3000, () => {
  console.log(`Server running on port ${port}`);
});