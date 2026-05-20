const readFileSync = require("./readFile.js");

function runCommand(content){
    const isFile = content[0] == '"';
    if(isFile){
        return readFileSync(content.slice(1, -1));
    }
    return content
}

function processString(inputString, input) {
  // Regex to find all {content} patterns
  const regex = /{([^}]+)}/g;
  
  // Replace each match with the result from runCommand
  return inputString.replace(regex, (match, contentInsideBraces) => {
    // Trim whitespace from the captured content
    const cleanContent = contentInsideBraces.trim();
    if(cleanContent == "input"){
        return input
    }
    // Pass to runCommand and return the result
    return runCommand(cleanContent);
  });
}

module.exports = processString;