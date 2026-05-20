const fs = require('fs');
const path = require('path');

// Function to read file content synchronously
function readFileSync(filePath) {
  try {
    const content = fs.readFileSync(path.resolve(filePath), 'utf8');
    return content;
  } catch (err) {
    console.error('Error reading file:', err);
    return null;
  }
}

// Export the function
module.exports = readFileSync;