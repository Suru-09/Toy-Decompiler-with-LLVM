import express, {Request, Response} from 'express';
import multer from 'multer';

import {spawn} from 'child_process';
import fs from 'fs';
import path from 'path';

const router = express.Router();

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
/*  ALL ROUTES FOR REST LIFTING SERVER (GET & POST for now)         */
/************************************************************/

router.get('/hello', (req, res) => {
  res.send('Hello, world!');
});


// POST FOR BINARY FILE
router.post('/upload', upload.single('file'), (req: Request, res: Response) => {
    if (!req.file) {
      return res.status(400).json({ message: 'No file uploaded' });
    }

    res.status(200).json({ message: `File ${req.file} been uploaded successfully` });
});

// ASK IF BINARY FILE WAS UPLOADED
router.get('/exist', (req: Request, res: Response) => {
    const file  = req.query.file;
    if(!file) {
        return res.status(400).json({ message: 'Key called <file> missing from GET request!' });
    }

    const filePath: string = "uploads/" + file;
    if(!fs.existsSync(filePath)) {
        return res.status(400).json({ message: `File ${file} does not exist at: ${filePath}` });
    }
    else { // file exists
        return res.status(200).json({ message: `File ${file} exists` });
    }
});

// IF BINARY FILE WAS UPLOADED, START LIFTING IT
router.post('/lift-executable', (req: Request, res: Response) => {
    const { file } = req.body;
    if(file) {
        return res.status(400).json({ message: 'Key called <file> missing from GET request!' });
    }
  
    var binaryPath: string = path.join(__dirname, '../../binary/retdec/bin/retdec-decompiler');
    var filePath: string = path.join(__dirname, '../../uploads/loops');
    const args: string[] = [filePath, "--print-after-all"];
    const childProcess = spawn(binaryPath, args, {shell: true, stdio: ['ignore', fs.openSync('./gen/loops.ll', 'w'), fs.openSync('./gen/loops.ll', 'w')]});

    if(!fs.existsSync(binaryPath)) {
        return res.status(400).json({ message: `File ${file} does not exist at: ${binaryPath}` });
    }

    if(!fs.existsSync(filePath)) {
        return res.status(400).json({ message: `File ${file} does not exist at: ${filePath}` });
    }
  
    // Listen for child process exit event
    childProcess.on('exit', (code: number) => {
      // Send response when child process has finished
      if(code !== 0) {
          return res.status(400).json({ message: `Execution failed!`});
      }

      const oldPath: string = "loops.ll";
      const newPath: string  = "gen/loops.ll";
      fs.rename(oldPath, newPath, (err) => {
            if(err) {
                return res.status(400).json({ message: `Error while renaming file: ${err}`});
            }
      });
      res.status(200).json({ message: `Execution for file: ${filePath} and binary with path: ${binaryPath} finished with code ${code}` });
    });
});

// ASK IF IR FILE HAS BEEN CREATED
router.get('/ir-exist', (req: Request, res: Response) => {
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
router.get('/ir', (req: Request, res: Response) => {
    if(!req.file) { // if no file was uploaded
        return res.status(400).json({ message: 'Key called <file> missing from GET request!' });
    }

    const filePath: string = "gen/" + req.file;
    const fileContents = fs.readFileSync(filePath, 'utf8');
    return res.status(200).json({ message: fileContents });
});

export default router;