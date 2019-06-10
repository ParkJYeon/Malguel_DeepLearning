# Malguel_DeepLearning

<darknet>
imge_opencv.cpp : darknet에서 프레임별로 인식한 값들을 출력하는 코드( draw_detections_cv_v3 메소드)
obj.data : darknet 학습 위한 data 정보 담긴 파일
obj.name : darknet 인지 클래스 (총 6개)
yolo-obj.cfg : darknet cnn layer의 구조 정의하는 파일 ( 분류된 클래스의 개수에 따라 변동)

<server>
index.js : 서버 작동 코드로 영상을 받아 저장하고, darknet을 실행시키고 json 형식으로 결과 전송하는 동작을 가짐

<추출 텍스트로 결과 인지하는 프로그램>
main.c : darknet을 통해 75%이상의 정확도를 가지고 추출된 결과들 중 최다 빈도로 나온 값을 찾는 코드

darknet, 서버의 파일이 많아서 직접 사용한 소스코드만 첨부합니다. 감사합니다.
