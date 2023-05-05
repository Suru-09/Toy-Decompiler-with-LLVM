"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const express_1 = __importDefault(require("express"));
const routes_1 = __importDefault(require("./routes/routes"));
const bodyParser = require('body-parser');
const app = (0, express_1.default)();
// octet-stream for binary file
app.use(bodyParser.raw({ type: 'application/octet-stream', limit: '2mb' }));
// json for everything else hopefully
app.use(express_1.default.json());
// Server PORT
const port = process.env.PORT || 29200;
const HOST = process.env.HOST || '0.0.0.0';
app.use('/api', routes_1.default);
app.get('/', (req, res) => {
    res.status(200).json({ message: 'Hello, world!' });
});
// message to console the PORT for the server
app.listen(port, HOST, () => {
    console.log(`Server running on port ${port}`);
});
