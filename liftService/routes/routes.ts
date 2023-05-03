import express, {Request, Response} from 'express';
import multer from 'multer';

import {spawn} from 'child_process';
import fs from 'fs';
import {readdirSync, unlinkSync} from 'fs';
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

const deleteFilesInDirectory = (directoryPath: string): void => {
    const files = readdirSync(directoryPath);
    for (const file of files) {
        const filePath = `${directoryPath}/${file}`;
        unlinkSync(filePath);
        console.log(`Deleted file: ${filePath}`);
    }
};

/************************************************************/
/*  ALL ROUTES FOR REST LIFTING SERVER (GET & POST for now) */
/************************************************************/

router.get('/hello', (req, res) => {
  res.status(200).json({ message: 'Hello, world!'});
});


// POST FOR BINARY FILE
router.post('/upload', upload.single('file'), (req: Request, res: Response) => {
   console.log("Post for file: " + req.file);
   if (!req.file) {
      return res.status(400).json({ message: 'No file uploaded' });
   }
   console.log(req.body);

    res.status(200).json({ message: `File ${req.file} been uploaded successfully` });
});

// ASK IF BINARY FILE WAS UPLOADED
// router.get('/exist', (req: Request, res: Response) => {
//     const file  = req.query.file;
//     if(!file) {
//         return res.status(400).json({ message: 'Key called <file> missing from GET request!' });
//     }

//     const filePath: string = "uploads/" + file;
//     if(!fs.existsSync(filePath)) {
//         return res.status(400).json({ message: `File ${file} does not exist at: ${filePath}` });
//     }
//     else { // file exists
//         return res.status(200).json({ message: `File ${file} exists` });
//     }
// });

// IF BINARY FILE WAS UPLOADED, START LIFTING IT
router.post('/decompile', (req: Request, res: Response) => {
    console.log(req);	
    const executable = req.body.file;
    if(!executable) {
        return res.status(400).json({ message: 'Key called <file> missing from GET request!' });
    }
  
    var pathToRetdec: string = "../../binary/retdec/bin/retdec-decompiler";
    var uploadsPath: string = "../../uploads/";
    var binaryPath: string = path.join(__dirname, pathToRetdec);
    var filePath: string = path.join(__dirname, '../../uploads/loops');

    console.log("Binary path: " + binaryPath);
    const args: string[] = [filePath];
    // TODO: add WSL support for Windows
    const childProcess = spawn(binaryPath, args, {shell: true});
    console.log("Child process: ");

    if(!fs.existsSync(binaryPath)) {
        return res.status(400).json({ message: `File ${executable} does not exist at: ${binaryPath}` });
    }

    if(!fs.existsSync(filePath)) {
        return res.status(400).json({ message: `File ${executable} does not exist at: ${filePath}` });
    }
  
    // Listen for child process exit event
    childProcess.on('exit', (code: number) => {
      // Send response when child process has finished
      if(code !== 0) {
          return res.status(400).json({ message: `Execution failed!`});
      }
      
      const generatedDir = path.join(__dirname, "../../gen/");
      if (!fs.existsSync(generatedDir))
      {
	 fs.mkdir(generatedDir, (err) => {
	    if(err) {
	    	console.log("Could not create dir: " + generatedDir);
	    }
	    else {
	    	console.log("Dir gen has been created at: " + generatedDir);
	    }		    
	 });
      }	      
      const oldPath: string = path.join(__dirname, "../../uploads/" + "loops" + ".ll");
      const newPath: string  = path.join(__dirname, "../../gen/" + "loops" + ".ll");
      console.log("Old path: " + oldPath);
      console.log("New path: " + newPath);
      try {
        fs.copyFileSync(oldPath, newPath)
      }
      catch(err) {
        return res.status(400).json({ message: `File ${executable} could not be copied to gen folder!}`});
      }

      try {
        deleteFilesInDirectory(path.join(__dirname, "../../uploads/"));
      }
      catch(err) {
        return res.status(400).json({ message: `Files in uploads folder could not be deleted!}`});
      }

      res.status(200).json({ message: `Execution for file: ${filePath} and binary with path: ${binaryPath} finished with code ${code}` });
    });
});

// ASK IF IR FILE HAS BEEN CREATED
router.get('/ir-exist', (req: Request, res: Response) => {
    const file = req.query.file;
    if(!file) {
        return res.status(400).json({ message: 'Key called <file> missing from GET request!' });
    }

    const filePath: string = path.join(__dirname, "../../gen/" + file + ".ll");
    if(!fs.existsSync(filePath)) {
        return res.status(400).json({ message: `File ${filePath} does not exist` });
    }
    else { // file exists
        return res.status(200).json({ message: `File ${file} exists` });
    }
});

// GET IR FILE
router.get('/ir', (req: Request, res: Response) => {
    const file = req.query.file;
    if(!file) { // if no file was uploaded
        return res.status(400).json({ message: 'Key called <file> missing from GET request!' });
    }

    const filePath: string = path.join(__dirname, "../../gen/" + file + ".ll");
    const fileContents = fs.readFileSync(filePath, 'utf8');
    return res.status(200).json({ message: fileContents });
});

export default router;
