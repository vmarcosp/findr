#!/usr/bin/env node

const { execSync } = require('child_process');
const fs = require('fs');
const path = require('path');
const packageJson = require('../package.json');

const filesToCopy = ['LICENSE', 'README.md'];

function exec(cmd) {
  console.log(`exec: ${cmd}`);
  return execSync(cmd).toString();
}

function mkdirpSync(p) {
  if (fs.existsSync(p)) {
    return;
  }
  mkdirpSync(path.dirname(p));
  fs.mkdirSync(p);
}

function removeSync(p) {
  exec(`rm -rf "${p}"`);
}

const src = path.resolve(path.join(__dirname, '..'));
const dst = path.resolve(path.join(__dirname, '..', '_release'));

removeSync(dst);
mkdirpSync(dst);

for (const file of filesToCopy) {
  const p = path.join(dst, file);
  mkdirpSync(path.dirname(p));
  fs.copyFileSync(path.join(src, file), p);
}

fs.copyFileSync(
  path.join(src, 'scripts', 'release-postinstall.js'),
  path.join(dst, 'postinstall.js')
);

const filesToTouch = ['findr.exe'];

for (const file of filesToTouch) {
  const p = path.join(dst, file);
  mkdirpSync(path.dirname(p));
  fs.writeFileSync(p, '');
}

const pkgJson = {
  name: `@vmarcosp/${packageJson.name}`,
  version: packageJson.version,
  description: packageJson.description,
  homepage: packageJson.homepage,
  license: packageJson.license,
  repository: packageJson.repository,
  scripts: {
    postinstall: 'node postinstall.js',
  },
  bin: {
    'findr': 'findr.exe',
  },
  files: [
    'platform-linux-x64/',
    'platform-darwin-x64/',
    'postinstall.js',
    'findr.exe',
  ],
};

fs.writeFileSync(
  path.join(dst, 'package.json'),
  JSON.stringify(pkgJson, null, 2)
);
