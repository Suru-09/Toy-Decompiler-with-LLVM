"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const express_1 = __importDefault(require("express"));
const child_process_1 = require("child_process");
const multer_1 = __importDefault(require("multer"));
const fs_1 = __importDefault(require("fs"));
const app = (0, express_1.default)();
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
/************************************************************/
/*  ALL ROUTES FOR REST SERVER (GET & POST for now)         */
/************************************************************/
// DEFAULT ROUTE
app.get('/', (req, res) => {
    res.send('Hello World!');
});
// POST FOR BINARY FILE
app.post('/api/upload', upload.single('file'), (req, res) => {
    if (!req.file) {
        return res.status(400).json({ message: 'No file uploaded' });
    }
    res.status(200).json({ message: `File ${req.file} been uploaded successfully` });
});
// ASK IF BINARY FILE WAS UPLOADED
app.get('/api/exist', (req, res) => {
    if (!req.file) {
        return res.status(400).json({ message: 'Key called <file> missing from GET request!' });
    }
    const filePath = "uploads/" + req.file;
    if (!fs_1.default.existsSync(filePath)) {
        return res.status(400).json({ message: `File ${req.file} does not exist` });
    }
    else { // file exists
        return res.status(200).json({ message: `File ${req.file} exists` });
    }
});
// IF BINARY FILE WAS UPLOADED, START LIFTING IT
app.post('/api/lift-executable', (req, res) => {
    if (!req.file) {
        return res.status(400).json({ message: 'Key called <file> missing from GET request!' });
    }
    // Spawn child process to run executable
    const args = [`${req.file}`, "--print-after-all"];
    const childProcess = (0, child_process_1.spawn)('binary/retdec-decompiler', args);
    // Listen for child process exit event
    childProcess.on('exit', (code) => {
        // Send response when child process has finished
        res.status(200).json({ message: `Execution finished with code ${code}` });
    });
    // Send response immediately to notify user that server is running the executable
    res.status(200).json({ message: 'Executing...' });
});
// ASK IF IR FILE HAS BEEN CREATED
app.get('/api/ir-exist', (req, res) => {
    if (!req.file) {
        return res.status(400).json({ message: 'Key called <file> missing from GET request!' });
    }
    const filePath = "gen/" + req.file;
    if (!fs_1.default.existsSync(filePath)) {
        return res.status(400).json({ message: `File ${req.file} does not exist` });
    }
    else { // file exists
        return res.status(200).json({ message: `File ${req.file} exists` });
    }
});
// GET IR FILE
app.get('/api/ir', (req, res) => {
    if (!req.file) { // if no file was uploaded
        return res.status(400).json({ message: 'Key called <file> missing from GET request!' });
    }
    const filePath = "gen/" + req.file;
    const fileContents = fs_1.default.readFileSync(filePath, 'utf8');
    return res.status(200).json({ message: fileContents });
});
// Server PORT
const port = process.env.PORT || 3000;
// message to console the PORT for the server
app.listen(3000, () => {
    console.log(`Server running on port ${port}`);
});
