const path = require('path')
const PACKAGE_JSON_PATH = path.join(__dirname, '..', '_release', 'package.json')
const packageJson = require(PACKAGE_JSON_PATH)
const fs = require('fs')

const namespace = '@vmarcosp'

const newPackageJson = JSON.stringify({
  ...packageJson,
  name: `${namespace}/${packageJson.name}`
}, null, '\t')

fs.writeFileSync(PACKAGE_JSON_PATH, newPackageJson)

