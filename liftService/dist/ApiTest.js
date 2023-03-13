"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const chai_1 = require("chai");
const mocha_1 = require("mocha");
const express_1 = __importDefault(require("express"));
const supertest_1 = __importDefault(require("supertest"));
const app = (0, express_1.default)();
(0, mocha_1.describe)('REST API tests', () => {
    (0, mocha_1.it)('should return Hello, world!', () => __awaiter(void 0, void 0, void 0, function* () {
        const res = yield (0, supertest_1.default)(app).get('/api/hello');
        (0, chai_1.expect)(res.statusCode).equal(200);
        //expect(res.body.message).equal('Hello, world!');
    }));
    (0, mocha_1.it)('should return a 404 error when no file is uploaded', () => __awaiter(void 0, void 0, void 0, function* () {
        const res = yield (0, supertest_1.default)(app).post('/api/upload');
        (0, chai_1.expect)(res.statusCode).equal(400);
        (0, chai_1.expect)(res.body.message).equal('No file uploaded');
    }));
    (0, mocha_1.it)('should return a 400 error when the file does not exist', () => __awaiter(void 0, void 0, void 0, function* () {
        const res = yield (0, supertest_1.default)(app).get('/exist?file=nonexistentfile');
        (0, chai_1.expect)(res.statusCode).equal(400);
        (0, chai_1.expect)(res.body.message).equal('File nonexistentfile does not exist at: uploads/nonexistentfile');
    }));
    (0, mocha_1.it)('should return a 200 status code and message when the file exists', () => __awaiter(void 0, void 0, void 0, function* () {
        const res = yield (0, supertest_1.default)(app).get('/exist?file=testfile');
        (0, chai_1.expect)(res.statusCode).equal(200);
        (0, chai_1.expect)(res.body.message).equal('File testfile exists');
    }));
    (0, mocha_1.it)('should return a 400 error when the executable key is missing', () => __awaiter(void 0, void 0, void 0, function* () {
        const res = yield (0, supertest_1.default)(app).post('/lift-executable');
        (0, chai_1.expect)(res.statusCode).equal(400);
        (0, chai_1.expect)(res.body.message).equal('Key called <file> missing from GET request!');
    }));
    (0, mocha_1.it)('should return a 400 error when the binary file does not exist', () => __awaiter(void 0, void 0, void 0, function* () {
        const res = yield (0, supertest_1.default)(app).post('/lift-executable').send({ file: 'nonexistentfile' });
        (0, chai_1.expect)(res.statusCode).equal(400);
        (0, chai_1.expect)(res.body.message).equal('File nonexistentfile does not exist at: ../../binary/retdec/bin/retdec-decompiler');
    }));
    (0, mocha_1.it)('should return a 400 error when the input file does not exist', () => __awaiter(void 0, void 0, void 0, function* () {
        const res = yield (0, supertest_1.default)(app).post('/lift-executable').send({ file: 'testfile' });
        (0, chai_1.expect)(res.statusCode).equal(400);
        (0, chai_1.expect)(res.body.message).equal('File testfile does not exist at: /app/uploads/loops');
    }));
    (0, mocha_1.it)('should return a 200 status code and message when the child process has finished', () => __awaiter(void 0, void 0, void 0, function* () {
        const res = yield (0, supertest_1.default)(app).post('/lift-executable').send({ file: 'validfile' });
        (0, chai_1.expect)(res.statusCode).equal(200);
        (0, chai_1.expect)(res.body.message).equal('Execution for file: /app/uploads/loops and binary with path: ../../binary/retdec/bin/retdec-decompiler finished with code 0');
    }));
    (0, mocha_1.it)('should return a 400 error when the IR file does not exist', () => __awaiter(void 0, void 0, void 0, function* () {
        const res = yield (0, supertest_1.default)(app).get('/ir-exist?file=nonexistentfile');
        (0, chai_1.expect)(res.statusCode).equal(400);
        (0, chai_1.expect)(res.body.message).equal('File /app/gen/nonexistentfile.ll does not exist');
    }));
    (0, mocha_1.it)('should return a 200 status code and message when the IR file exists', () => __awaiter(void 0, void 0, void 0, function* () {
        const res = yield (0, supertest_1.default)(app).get('/ir-exist?file=testfile');
        (0, chai_1.expect)(res.statusCode).equal(200);
        (0, chai_1.expect)(res.body.message).equal('File testfile exists');
    }));
});
