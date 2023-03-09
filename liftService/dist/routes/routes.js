"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const express_1 = __importDefault(require("express"));
const multer_1 = __importDefault(require("multer"));
const child_process_1 = require("child_process");
const fs_1 = __importDefault(require("fs"));
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
/************************************************************/
/*  ALL ROUTES FOR REST LIFTING SERVER (GET & POST for now)         */
/************************************************************/
router.get('/hello', (req, res) => {
    res.send('Hello, world!');
});
// POST FOR BINARY FILE
router.post('/upload', upload.single('file'), (req, res) => {
    if (!req.file) {
        return res.status(400).json({ message: 'No file uploaded' });
    }
    res.status(200).json({ message: `File ${req.file} been uploaded successfully` });
});
// ASK IF BINARY FILE WAS UPLOADED
router.get('/exist', (req, res) => {
    const file = req.query.file;
    if (!file) {
        return res.status(400).json({ message: 'Key called <file> missing from GET request!' });
    }
    const filePath = "uploads/" + file;
    if (!fs_1.default.existsSync(filePath)) {
        return res.status(400).json({ message: `File ${file} does not exist at: ${filePath}` });
    }
    else { // file exists
        return res.status(200).json({ message: `File ${file} exists` });
    }
});
// IF BINARY FILE WAS UPLOADED, START LIFTING IT
router.post('/lift-executable', (req, res) => {
    const { file } = req.body;
    if (file) {
        return res.status(400).json({ message: 'Key called <file> missing from GET request!' });
    }
    var binaryPath = path_1.default.join(__dirname, '../../binary/retdec/bin/retdec-decompiler');
    var filePath = path_1.default.join(__dirname, '../../uploads/loops');
    const args = [filePath, "--print-after-all"];
    const childProcess = (0, child_process_1.spawn)(binaryPath, args, { shell: true, stdio: ['ignore', fs_1.default.openSync('./gen/loops.ll', 'w'), fs_1.default.openSync('./gen/loops.ll', 'w')] });
    if (!fs_1.default.existsSync(binaryPath)) {
        return res.status(400).json({ message: `File ${file} does not exist at: ${binaryPath}` });
    }
    if (!fs_1.default.existsSync(filePath)) {
        return res.status(400).json({ message: `File ${file} does not exist at: ${filePath}` });
    }
    // Listen for child process exit event
    childProcess.on('exit', (code) => {
        // Send response when child process has finished
        res.status(200).json({ message: `Execution for file: ${filePath} and binary with path: ${binaryPath} finished with code ${code}` });
    });
});
// ASK IF IR FILE HAS BEEN CREATED
router.get('/ir-exist', (req, res) => {
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
router.get('/ir', (req, res) => {
    if (!req.file) { // if no file was uploaded
        return res.status(400).json({ message: 'Key called <file> missing from GET request!' });
    }
    const filePath = "gen/" + req.file;
    const fileContents = fs_1.default.readFileSync(filePath, 'utf8');
    return res.status(200).json({ message: fileContents });
});
exports.default = router;
