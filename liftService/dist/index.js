"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const express_1 = __importDefault(require("express"));
const routes_1 = __importDefault(require("./routes/routes"));
const app = (0, express_1.default)();
app.use(express_1.default.json());
// Server PORT
const port = process.env.PORT || 3000;
app.use('/api', routes_1.default);
// message to console the PORT for the server
app.listen(3000, () => {
    console.log(`Server running on port ${port}`);
});
