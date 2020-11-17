'use strict';

module.exports = {
  up: (queryInterface, Sequelize) => {
    return queryInterface.bulkInsert('problem', [
      {
        userId: 1,
        title: "Yard(야적장)",
        description: "<p>주말에 큰 태풍이 예고되어 부산항 야적장에 쌓인 컨네이너를 아래 규칙으로 옮겨 사고를 대비한다.</p><br>\
          <p>(1) 가장 높은 위치의 컨테이너를 들어내어 가장 낮은 빈자리 자리로 옮긴다.</p>\
          <p>(2) 컨테이너는 항상 가장 위(top)에 있는 것만 움직일 수 있다.</p>\
          <p>(3) 같은 높이의 컨테이너가 하나 이상이면 더 무거운(더 큰 숫자)를 선택한다.</p>\
          <p>(4) 가장 낮은 자리가 하나 이상이면 적치장 번호가 빠른(작은) 곳을 선호한다.</p>\
          <p>(5) 가장 높은 적치장과 가장 낮은 적치장의 높이 차이가 1이하가 되면 멈춘다.</p><br>\
          <p>Step-0은 초기 상태이다. 먼저 가장 높은 높이=5에 있는 컨테이너 [19]를 들어내서 가장 낮은 자리로 옮긴다. 가장 낮은 자리는 높이 0인 자리가 {2, 6}이므로 더 빠른 자리 적치장 2번에 배치한다. Step-1에서 보면 가장 높은 것은 1번, 3번 적치장에 있는 {81, 40}인데 더 무거운 [81]을 움직여야 한다. 따라서 [81]을 가장 낮은 위치인 6번 적치장에 배치한다. 그 다음에는 3번 적치장 top의 [40]을 가장 낮은 것 중 가장 빠른 2번에 적치장에 놓는다. 그 결과는 Step-3과 같다. Step-4에서 [15]를 6번 적치장에 옮기고 나면 가장 높은 곳과 가장 낮은 곳의 차이가 1이 되므로 작업이 종료된다.</p>",
        memoryLim: 512,
        timeLim: 2,
        input: "<p>입력은 표준 입력(stdin)으로 받는다. 첫 줄에는 야적장의 개수 N () 이다. 이어지는 N개의 줄에는 번째 야적장에 쌓인 컨테이너의 갯수 가 주어지고 “>” 기호가 나온 뒤에 야적장에 쌓인 컨테이너의 ID(무게)가 밑에서부터 위로 개의 정수로 주어진다. 즉 입력 파일의 가장 오른쪽이 stack top의 원소이다. 단 야적장에는 반드시 1개 이상의 컨테이너가 있다. 만일 비어있으면  이다.</p>",
        output: "<p></p>",
        sampleInput: "7<br>\
          4 70 45 15 81<br>\
          0<br>\
          5 76 9 22 40 19<br>\
          1 67<br>\
          2 54 41<br>\
          0<br>\
          1 29",
        sampleOutput: "1 > 70 45<br>\
          2 > 19 40<br>\
          3 > 76 9<br>\
          4 > 67 22<br>\
          5 > 54 41<br>\
          6 > 81 15<br>\
          7 > 29",
        // create_at: new Date().toISOString().replace(/T/, ' ').replace(/\..+/, ''),
      },
      {
        userId: 2,
        title: "RobotCop(로보캅)",
        description: "<p>위험물 창고를 로봇이 그 경계를 돌면서 감시한다.</p>\
          <p>아래 그림에서 굵은 선으로 표시된 다각형이 경계면이다.</p>\
          <p>경계면은 수직, 수평 선분으로 구성된 단순 다각형이다.</p>\
          <p>이 경계의 한 시작점에서 로봇은 초당 1m씩 시계방향으로 경계를 따라 한 칸씩 움직인다.</p>\
          <p>예를 들어 (3,3)이 출발점이라면 4초 후에는 (3,7)점에, 20초 후에는 (13,6)에 있게 된다.</p>\
          <p>여러분은 초 후 로봇 좌표 를 계산해야 한다.</p>",
        memoryLim: 512,
        timeLim: 1,
        input: "<p>표준 입출력을 사용한다. 입력 파일의 첫 줄에는 창고 경계 꼭지점의 개수 가 주어진다.  이어지는 K개 줄에는 창고 꼭지점 좌표가 순서대로 주어진다. 첫 좌표는 감시 로봇의  출발점이며 입력 파일에 나타난 정점 순서대로 따라간다.   K는 50 이하이며 좌표 범위는  이다. 그리고 마지막 줄에 5개의 정수 가 주어진다. 여러분은 시각  일 때 로봇의 위치 좌표를 계산해서 5개 줄에 순서대로 출력해야 한다.</p>",
        output: "<p></p>",
        sampleInput: "12<br>\
          3 3<br>\
          3 7<br>\
          7 7<br>\
          7 10<br>\
          11 10<br>\
          11 6",
        sampleOutput: "3 4<br>\
          12 6<br>\
          6 7<br>\
          ...<br>\
          ...."
      },
      {
        userId: 3,
        title: "1",
        description: "1",
        memoryLim: 512,
        timeLim: 1,
        input: "1",
        output: "1",
        sampleInput: "1",
        sampleOutput: "1"
      },
      {
        userId: 4,
        title: "2",
        description: "2",
        memoryLim: 512,
        timeLim: 1,
        input: "2",
        output: "2",
        sampleInput: "2",
        sampleOutput: "2"
      },
      {
        userId: 5,
        title: "3",
        description: "3",
        memoryLim: 512,
        timeLim: 1,
        input: "3",
        output: "3",
        sampleInput: "3",
        sampleOutput: "3"
      }
    ], {});
  },

  down: (queryInterface, Sequelize) => {
    return queryInterface.bulkDelete('problem', null, {});
  }
};