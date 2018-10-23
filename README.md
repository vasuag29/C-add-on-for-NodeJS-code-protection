# C-add-on-for-NodeJS-code-protection
This project aims at programming a C++ program with encryption/decryption methods that can be used as a native add-on for Node.

1) Create project folder and run following commands:
sudo npm i node-gyp -g
npm install nan --save
npm install bindings --save

2) Run npm installer:
npm init
npm install

3) Run configure command of node-gyp using following command:
sudo node-gyp configure

4) Build node-gyp using following command:
node-gyp build

5) Run node file:
node index.js (this file is just a sample driver code)

