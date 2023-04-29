import { expect } from 'chai';
import express from 'express';
import { describe, it } from 'mocha';
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
});
