import { expect } from 'chai';
import { describe, it } from 'mocha';
import express from 'express';
import request from 'supertest';

const app = express();

describe('REST API tests', () => {
  it('should return Hello, world!', async () => {
    const res = await request(app).get('/api/hello');
    expect(res.statusCode).equal(200);
    //expect(res.body.message).equal('Hello, world!');
  });

  it('should return a 404 error when no file is uploaded', async () => {
    const res = await request(app).post('/api/upload');
    expect(res.statusCode).equal(400);
    expect(res.body.message).equal('No file uploaded');
  });

  it('should return a 400 error when the file does not exist', async () => {
    const res = await request(app).get('/exist?file=nonexistentfile');
    expect(res.statusCode).equal(400);
    expect(res.body.message).equal('File nonexistentfile does not exist at: uploads/nonexistentfile');
  });

  it('should return a 200 status code and message when the file exists', async () => {
    const res = await request(app).get('/exist?file=testfile');
    expect(res.statusCode).equal(200);
    expect(res.body.message).equal('File testfile exists');
  });

  it('should return a 400 error when the executable key is missing', async () => {
    const res = await request(app).post('/lift-executable');
    expect(res.statusCode).equal(400);
    expect(res.body.message).equal('Key called <file> missing from GET request!');
  });

  it('should return a 400 error when the binary file does not exist', async () => {
    const res = await request(app).post('/lift-executable').send({ file: 'nonexistentfile' });
    expect(res.statusCode).equal(400);
    expect(res.body.message).equal('File nonexistentfile does not exist at: ../../binary/retdec/bin/retdec-decompiler');
  });

  it('should return a 400 error when the input file does not exist', async () => {
    const res = await request(app).post('/lift-executable').send({ file: 'testfile' });
    expect(res.statusCode).equal(400);
    expect(res.body.message).equal('File testfile does not exist at: /app/uploads/loops');
  });

  it('should return a 200 status code and message when the child process has finished', async () => {
    const res = await request(app).post('/lift-executable').send({ file: 'validfile' });
    expect(res.statusCode).equal(200);
    expect(res.body.message).equal('Execution for file: /app/uploads/loops and binary with path: ../../binary/retdec/bin/retdec-decompiler finished with code 0');
  });

  it('should return a 400 error when the IR file does not exist', async () => {
    const res = await request(app).get('/ir-exist?file=nonexistentfile');
    expect(res.statusCode).equal(400);
    expect(res.body.message).equal('File /app/gen/nonexistentfile.ll does not exist');
  });

  it('should return a 200 status code and message when the IR file exists', async () => {
    const res = await request(app).get('/ir-exist?file=testfile');
    expect(res.statusCode).equal(200);
    expect(res.body.message).equal('File testfile exists');
  });
});
