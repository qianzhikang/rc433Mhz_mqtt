const fs = require("fs");

const staticToken = fs.readFileSync("./token/static", "utf8");

function check(req, res) {
  const token = req.headers["token"];
  if (token !== staticToken) {
    res.status(401).send({ msg: "Unauthorized" });
    return false;
  }
  return true;
}

module.exports = {
  check,
};
