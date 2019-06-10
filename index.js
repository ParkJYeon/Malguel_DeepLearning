var express = require('express');
var fs = require("fs");
var lineReader = require("line-reader");
var done = false;
var multer = require('multer');
var bodyParser = require("body-parser");
var path = require('path');


var count = 0;
var str = {};

var router = express();

const exec = require('child_process').exec;
var cmd1 = 'darknet.exe detector demo data\\obj.data yolo-obj.cfg backup\\yolo-obj_10000.weights uploads\\video_recorded.mp4 -dont_show';
var cmd2 = 'D:\\take_result\\TakeResult\\Debug\\TakeResult.exe';


router.use(bodyParser.json());
router.use(bodyParser.urlencoded({extended: true}));
router.use(function(req, res, next){
  res.header("Access-Control-Allow-Origin", "*");
  res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
  next();
});

var storage = multer.diskStorage({
  destination: function(request, file, callback){
    callback(null, './uploads');
  },
  filename: function(request, file, callback){
    console.log(file);
    callback(null, file.originalname);
  }
});

var upload = multer({storage: storage}).any('userPhoto');




/* GET home page. */

router.get('/', function(req, res, next) {
  exec(cmd1, function(error, stdout, stderr){
    console.log('stdout : ', stdout);
    console.log('stderr : ', stderr);
    
    if(error !== null){
        console.log('exe error: ', error);
                
    }else{
      exec(cmd2, function(error, stdout, stderr){
        console.log('stdout : ', stdout);
        console.log('stderr : ', stderr);
    
        if(error !== null){
          console.log('exe error : ', error);
        }else{
          lineReader.eachLine('D:\\take_result\\TakeResult\\TakeResult\\result.txt', function(line, last){
            if(count == 0){
              str = filterFirstLine(line);
            }else{
              str['value'] = filterItems(line);
            }

            if(last){
              console.log('======== parsing is done! ========');
              makeFile(JSON.stringify(str));
            }
          });

          function makeFile(str){

            let result = [
              {
                result: str
              }
            ]

            res.json(result);
          }

          function filterFirstLine(line){
            var arr = line.split("\t");
            return arr;
          }

          function filterItems(line){
            var arr = line.split("\t");
            var obj = {};

            if(arr.length == 1){
              obj.value = arr[0];
            }
            if(arr.length == 0){
              obj.value = 'null';
            }

            return obj;
          }
        }
      });
    }
  });
});

router.listen(3000, () => {
  console.log('App listening on port 2000');
});

router.post('/api/photo', (req, res) => {
  upload(req,res,function(err) {
		if(err) {
      console.log('ERR');
			return res.end("Error uploading file.");
    }
    console.log('OK');
		res.end("File is uploaded\n " + JSON.stringify(req.files));
	});
})

module.exports = router;


