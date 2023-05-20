"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const express_1 = __importDefault(require("express"));
const multer_1 = __importDefault(require("multer"));
const child_process_1 = require("child_process");
const fs_1 = __importDefault(require("fs"));
const fs_2 = require("fs");
const path_1 = __importDefault(require("path"));
const router = express_1.default.Router();
// Middleware to parse JSON body
const upload = (0, multer_1.default)({
    storage: multer_1.default.diskStorage({
        destination: (req, file, cb) => {
            cb(null, 'uploads/'); // save files to the 'uploads' directory
        },
        filename: (req, file, cb) => {
            cb(null, file.originalname); // use original filename
        },
    }),
});
const deleteFilesInDirectory = (directoryPath) => {
    const files = (0, fs_2.readdirSync)(directoryPath);
    for (const file of files) {
        const filePath = `${directoryPath}/${file}`;
        (0, fs_2.unlinkSync)(filePath);
        console.log(`Deleted file: ${filePath}`);
    }
};
/************************************************************/
/*  ALL ROUTES FOR REST LIFTING SERVER (GET & POST for now) */
/************************************************************/
router.get('/hello', (req, res) => {
    res.status(200).json({ message: 'Hello, world!' });
});
// POST FOR BINARY FILE
router.post('/upload', upload.single('file'), (req, res) => {
    const uploadsDir = path_1.default.join(__dirname, "../../uploads/");
    if (!fs_1.default.existsSync(uploadsDir)) {
        fs_1.default.mkdir(uploadsDir, (err) => {
            if (err) {
                console.log("Could not create dir: " + uploadsDir);
            }
            else {
                console.log("Dir uploads has been created at: " + uploadsDir);
            }
        });
    }
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
router.post('/decompile', (req, res) => {
    const executable = req.body.file;
    if (!executable) {
        return res.status(400).json({ message: 'Key called <file> missing from GET request!' });
    }
    var pathToRetdec = "../../binary/retdec/bin/retdec-decompiler";
    var uploadsPath = "../../uploads/";
    var binaryPath = path_1.default.join(__dirname, pathToRetdec);
    var filePath = path_1.default.join(__dirname, '../../uploads/' + executable);
    console.log("Binary path: " + binaryPath);
    const args = [filePath];
    // TODO: add WSL support for Windows
    const childProcess = (0, child_process_1.spawn)(binaryPath, args, { shell: true });
    console.log("Child process: ");
    if (!fs_1.default.existsSync(binaryPath)) {
        return res.status(400).json({ message: `File ${executable} does not exist at: ${binaryPath}` });
    }
    if (!fs_1.default.existsSync(filePath)) {
        return res.status(400).json({ message: `File ${executable} does not exist at: ${filePath}` });
    }
    // Listen for child process exit event
    childProcess.on('exit', (code) => {
        // Send response when child process has finished
        if (code !== 0) {
            return res.status(400).json({ message: `Execution failed!` });
        }
        const generatedDir = path_1.default.join(__dirname, "../../gen/");
        if (!fs_1.default.existsSync(generatedDir)) {
            fs_1.default.mkdir(generatedDir, (err) => {
                if (err) {
                    console.log("Could not create dir: " + generatedDir);
                }
                else {
                    console.log("Dir gen has been created at: " + generatedDir);
                }
            });
        }
        console.log("File gen was created/already existed.");
        const oldPath = path_1.default.join(__dirname, "../../uploads/" + executable + ".ll");
        const newPath = path_1.default.join(__dirname, "../../gen/" + executable + ".ll");
        console.log("Old path: " + oldPath);
        console.log("New path: " + newPath);
        try {
            fs_1.default.copyFileSync(oldPath, newPath);
        }
        catch (err) {
            return res.status(400).json({ message: `File ${executable} could not be copied to gen folder!}` });
        }
        try {
            deleteFilesInDirectory(path_1.default.join(__dirname, "../../uploads/"));
        }
        catch (err) {
            return res.status(400).json({ message: `Files in uploads folder could not be deleted!}` });
        }
        res.status(200).json({ message: `Execution for file: ${filePath} and binary with path: ${binaryPath} finished with code ${code}` });
    });
    // childProcess.stdout.on('data', (data) => {
    //   console.log(`Decompile stdout: ${data}`);
    // });
    // childProcess.stderr.on('data', (data) => {
    //   console.error(`Decompile stderr: ${data}`);
    // });
});
// ASK IF IR FILE HAS BEEN CREATED
router.get('/ir-exist', (req, res) => {
    const file = req.query.file;
    if (!file) {
        return res.status(400).json({ message: 'Key called <file> missing from GET request!' });
    }
    const filePath = path_1.default.join(__dirname, "../../gen/" + file + ".ll");
    if (!fs_1.default.existsSync(filePath)) {
        return res.status(400).json({ message: `File ${filePath} does not exist` });
    }
    else { // file exists
        return res.status(200).json({ message: `File ${file} exists` });
    }
});
// GET IR FILE
router.get('/ir', (req, res) => {
    const file = req.query.file;
    console.log("Get IR for: " + file);
    if (!file) { // if no file was uploaded
        return res.status(400).json({ message: 'Key called <file> missing from GET request!' });
    }
    const filePath = path_1.default.join(__dirname, "../../gen/" + file + ".ll");
    console.log("File path for reading the generated file: " + filePath);
    if (!fs_1.default.existsSync(filePath)) {
        return res.status(400).json({ message: `File ${filePath} does not exist` });
    }
    const fileContents = fs_1.default.readFileSync(filePath, 'utf8');
    return res.status(200).json({ message: fileContents });
});
exports.default = router;
