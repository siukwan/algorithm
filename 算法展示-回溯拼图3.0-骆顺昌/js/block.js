//颜色集
var colors = ["#213450", "#D071BA", "orange", "#113228", "#00ff00", "black", "#482060", "#2A110E", "#6868ff", "#ff6868", "#68FF68", "yellow", "#F0F5FA", "red"]; //12种
var p_result = document.getElementById("showResult"); //显示运算过程
var result_str = "运算过程：<br>"; //运算过程
var right_result = [6, 12, 1, 10, 5, 2, 7, 8, 9, 11, 3, 4]; //结果正确的解	        
var result = [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]; //测试解
var pointer = 0; //指向result的当前位置
var run_search;//用于暂停
var flag_pause=0;
var intervalTime_global;
var shape_rotate=getRotateShape();//包含旋转块的矩阵

var shape = new Array();
shape[0] = [5, 0, 5, 1, 5, 2, 4, 2, 3, 2];
shape[1] = [3, 3, 4, 3, 5, 3, 3, 4, 5, 4];
shape[2] = [0, 7, 0, 8, 0, 9, 1, 8, 1, 9];
shape[3] = [5, 8, 5, 9, 4, 9, 3, 9, 2, 9];
shape[4] = [1, 2, 1, 3, 2, 3, 2, 4, 2, 5];
shape[5] = [0, 0, 1, 0, 2, 0, 3, 0, 1, 1];
shape[6] = [1, 4, 1, 5, 1, 6, 0, 6, 2, 6];
shape[7] = [4, 4, 3, 5, 4, 5, 5, 5, 4, 6];
shape[8] = [3, 6, 3, 7, 2, 7, 1, 7, 2, 8];
shape[9] = [0, 1, 0, 2, 0, 3, 0, 4, 0, 5];
shape[10] = [5, 6, 5, 7, 4, 7, 4, 8, 3, 8];
shape[11] = [4, 0, 4, 1, 3, 1, 2, 1, 2, 2];




/**
*函数：画图拼图
*/
function drawBlock(block) {
	//alert(result);
	var shape_selected;
	for(i_selected=0;i_selected<12;i_selected++){
		if(result[i_selected]!=0) shape_selected=result[i_selected]-1;
	}	
	drawCutline(shape_selected);
    //第一步：获取canvas元素
    var canvasDom = document.getElementById("demoCanvas");
    //第二步：获取上下文
    var context = canvasDom.getContext('2d');
	//清除画布
	context.clearRect(0,0,400,600);
	//画外部的大边框
	context.lineWidth = 3;
    context.strokeStyle = 'black';
    context.strokeRect(10, 10, 320, 520);

    len = 50; //每个格子的边长
    for (var i = 0; i <= 9; i++) {
        for (var j = 0; j <= 5; j++) {
            n_order = 6 * i + j;
            //fill_color='#'+('00000'+(Math.random()*0x1000000<<0).toString(16)).slice(-6);
            //fill_color=colors[Math.round(Math.random()*11)+1];
            fill_color = colors[block[i][j]]; //选择颜色
            position_x = 20 + len * (j); //横坐标
            position_y = 20 + len * (i); //纵坐标
            context.fillStyle = fill_color; //填入颜色
            context.fillRect(position_x, position_y, len - 5, len - 5); //画出格子
			if(block[i][j]==shape_selected || block[i][j]==13){
				context.lineWidth = 3;
				context.strokeStyle = 'red';
				context.strokeRect(position_x-2.5, position_y-2.5, len, len);
			}else{
				//context.strokeStyle = 'white';
				//context.lineWidth = 2.5;
				//context.strokeRect(position_x-2.5, position_y-2.5, len, len);
			}
        }
    }
}

/**
        *函数：先产生block，再画出来
        *result是解
        */
function createBlock(result) {
    var block = new Array();
    //初始化block
    for (i = 0; i <= 9; i++) {
        var block_row = new Array();
        for (j = 0; j <= 5; j++) {
            //block_row[j]=Math.round(Math.random()*11)+1;//对应颜色的序号
            block_row[j] = 12;
        }
        block[i] = block_row;
    }
    //alert(block);
    x_null = 0;
    y_null = 0;
    for (i = 0; i <= 11; i++) {
        if (result[i] == 0) {
            //画出block
            drawBlock(block);
            return true; //碰到0，说明还没填满格子
        }
        bi = shape[result[i] - 1];
        //alert(bi);
        flag_no_null = 0;
        //找出还没有被标的位置x_null,y_null
        while (y_null <= 9 & x_null <= 5 && block[y_null][x_null] != 12) {
            if (block[y_null][x_null] == 12) {
                break;
            } else {
                x_null++;
                if (x_null == 6) {
                    y_null++;
                    x_null = 0;
                }
            }

        }

        if (y_null > 9) {
            flag_no_null = 1; //找不到空格子	
            return false;
        }

        //alert("x_null:"+x_null+"\ny_null:"+y_null);
        flag_overlap = 0;
        flag_overIndex = 0;
        for (j = 0; j <= 4; j++) {
            x = x_null + bi[j * 2] - bi[0];
            y = y_null + bi[j * 2 + 1] - bi[1];
            if (x >= 0 && x <= 5 && y >= 0 && y <= 9) {
                if (block[y][x] == 12 && flag_overlap == 0) {
                    block[y][x] = result[i] - 1; //填入相应的块序号
                } else {
                    block[y][x] = 13; //重叠的地方标为红色
                    flag_overlap = 1; //有重叠
                }
            } else {
                flag_overIndex = 1; //下标越界
            }
        }
        if (flag_overlap || flag_overIndex || flag_no_null) {
            //画出block
            drawBlock(block);
            return false;
        }
    }
    //画出block
    drawBlock(block);
    return true;
}

/**
*函数：搜索拼图一次
*/
function search_one_step() {
    for (kk = 1; kk < 2; kk++) { 
		var p_result = document.getElementById("showResult");
		p_result.innerHTML=getResultHtml(result);
		isNoWrong = createBlock(result);
        if (isNoWrong) {
            pointer++;
            if (pointer == 12) {
				//将状态恢复到最初状态，便于下一次演示
				result = [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]; //测试解
				pointer = 0; //指向result的当前位置
				clearInterval(run_search);
                break;
            }
            result[pointer] = getNext(result, pointer);
            //result_str = result_str + "<br>完成下一个：" + result + "  P:" + pointer;
        } else {
            getAddSelf();
            //result_str = result_str + "<br>自我增加后：" + result + "  P:" + pointer;
        }
    }
}

/**
*函数：开始搜索拼图
*/
function start_search(intervalTime) {
	clearInterval(run_search);
	intervalTime_global=intervalTime;
    run_search=setInterval("search_one_step()", intervalTime);
}

/**
*函数：result获得填一个格子的序列
*/
function getNext() {
    //result=[6,12,1,10,5,2,7,8,9,0,0,0];
    //pointer=9;
    var i = 1;
    var j = 0;
    for (i = 1; i <= 12; i++) {
        var flag = 0;
        for (j = 0; j <= pointer; j++) {
            if (i == result[j]) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            //alert(result+"\np:"+pointer+"i:"+i);
            return i;
        }
    }
    return i;
}

/**
*函数：搜索回溯时，选一个格子尝试。
*/
function getAddSelf() {
    //result=[6,12,1,10,5,2,7,8,3,11,0,0];
    //pointer=9;
	//alert("start to add\n"+result+"\n"+pointer);
    var flag;
    while (true) {
        result[pointer]=result[pointer]+1;
        a = result[pointer];
        if (a > 12) {
            result[pointer] = 0;
            pointer = pointer - 1;
        } else {
            flag = 0;
            for (var i = 0; i < pointer; i++) {
                if (a == result[i]) {
                    flag = 1;
                }
            }
            if (flag == 0) {
                //alert(result+"\n"+pointer);
                return a;
            }
        }
    }
}

/**
*函数：清空格子
*/
function clearBlock() {
	clearInterval(run_search);
	result_str = "运算过程：<br>"; //运算过程      
	result = [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]; //测试解
	pointer = 0; //指向result的当前位置
    var block = new Array();
    //初始化block
    for (i = 0; i <= 9; i++) {
        var block_row = new Array();
        for (j = 0; j <= 5; j++) {
            block_row[j] = 12;
        }
        block[i] = block_row;
    }
    drawBlock(block);
	var p_result = document.getElementById("showResult");
	p_result.innerHTML=getResultHtml([0,0,0,0,0,0,0,0,0,0,0,0]);
}

/**
*函数：暂停
*/
function pause_search(){
	
	var pauseButt_text= document.getElementById("pauseButton"); //显示运算过程
	if(flag_pause==0){
		clearInterval(run_search);
		flag_pause=1;
		pauseButt_text.innerHTML="继续";
	}else{
		flag_pause=0;
		pauseButt_text.innerHTML="暂停";
		clearInterval(run_search);
		run_search=setInterval("search_one_step()", intervalTime_global);
	}
	
}

/**
*函数：结束搜索，直接给出答案
*/
function stop_search(){
	clearInterval(run_search);
	result=right_result;
	//显示最终结果
	createBlock(result);
	var p_result = document.getElementById("showResult");
	p_result.innerHTML=getResultHtml(result);
	result = [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]; //测试解
	pointer = 0; //指向result的当前位置
}

function drawCutline(shape_selected){
	//860，100
	var cutlineCanvas = document.getElementById("cutlineCanvas");//第一步：获取canvas元素
    var context = cutlineCanvas.getContext('2d');//第二步：获取上下文
	var i;
	var j;
	var n_row=10;
	var n_col=30;
	var grid_len=27;
	var grid_margin=1;
	//初始化cutline矩阵
	var cutline=new Array();
	var cutline_row=new Array();
	for(i=0;i<n_row;i++){
		var cutline_row=new Array();
		for(j=0;j<n_col;j++)
			cutline_row[j]=12;	
		cutline[i]=cutline_row;
	}
	x_origin=1;
	y_origin=1;
	//根据shape，将12块的序号填入cutline中shape
	for(i=0;i<12;i++){
		if(i==6){
			x_origin=1;
			y_origin=6;
		}
		if(i==9){
			y_origin=4;
		}
		if(i>9){
			y_origin=6;
		}
		x_min=12;
		y_min=12;
		x_max=0;
		for(j=0;j<5;j++){
			if(shape[i][j*2]<x_min) x_min=shape[i][j*2];
			if(shape[i][j*2]>x_max) x_max=shape[i][j*2];
			if(shape[i][j*2+1]<y_min) y_min=shape[i][j*2+1];
		}
		for(j=0;j<5;j++){
			x=x_origin+shape[i][j*2]-x_min;
			y=y_origin+shape[i][j*2+1]-y_min;
			cutline[y][x]=i;
			if(i==shape_selected) cutline[y][x]=13;//被选中的，则显示红色
			//alert("block"+i+":\nx是"+x+"\ny是"+y);
		}
		//alert(cutline);
		x_origin=x_origin+x_max+3-x_min;
	}

	//画出格子
	for(i=0;i<n_row;i++){
		for(j=0;j<n_col;j++){
			fill_color = colors[cutline[i][j]]; //选择颜色
			//fill_color=colors[Math.round(Math.random()*11)+1];
            position_x = grid_len* j; //横坐标
            position_y = grid_len*i; //纵坐标
            context.fillStyle = fill_color; //填入颜色
            context.fillRect(position_x, position_y, grid_len- grid_margin,grid_len- grid_margin); //画出格子	
		}
	}

	
}

function getResultHtml(result){
	var resultHtml="<table  height=85><tr>";
	for(var i=0;i<12;i++){
		switch(result[i]){
			case 0:resultHtml=resultHtml+"<td width=30></td>";break;
			case 10:resultHtml=resultHtml+"<td width=30>a</td>";break;
			case 11:resultHtml=resultHtml+"<td width=30>b</td>";break;
			case 12:resultHtml=resultHtml+"<td width=30>c</td>";break;
			default:resultHtml=resultHtml+"<td width=30>"+result[i]+"</td>";
		}
	}
	return resultHtml+"</tr></table>";
}

function drawRotateCutline(){
	//860，100
	var cutlineCanvas = document.getElementById("cutlineCanvas_rotate");//第一步：获取canvas元素
    var context = cutlineCanvas.getContext('2d');//第二步：获取上下文
	var i;
	var j;
	var n_row=54;
	var n_col=40;
	var x_origin_array=[1,1,1,1,1,1,1,1,1,1,1,1];
	var y_origin_array=[1,5,9,13,18,23,28,32,36,42,46,50];
	var n_shape_array=[4,4,8,8,8,8,4,1,8,2,4,4];
	var margin_grid=2;
	var grid_len=27;
	var grid_margin=1;
	
	//初始化cutline矩阵
	var cutline=new Array();
	var cutline_row=new Array();
	for(i=0;i<n_row;i++){
		var cutline_row=new Array();
		for(j=0;j<n_col;j++)
			cutline_row[j]=12;	
		cutline[i]=cutline_row;
	}

	//根据shape，将12块的序号填入cutline中shape
	for(i=0;i<12;i++){
		x_origin=x_origin_array[i];
		y_origin=y_origin_array[i];
		n_shape=n_shape_array[i];
		for(var k=0;k<n_shape;k++){
			x_min=12;
			y_min=12;
			x_max=0;
			if(i==9 && k==1){
				y_origin=y_origin-2;
			}
			for(j=0;j<5;j++){
				if(shape_rotate[i][k][j*2]<x_min) x_min=shape_rotate[i][k][j*2];
				if(shape_rotate[i][k][j*2]>x_max) x_max=shape_rotate[i][k][j*2];
				if(shape_rotate[i][k][j*2+1]<y_min) y_min=shape_rotate[i][k][j*2+1];
			}
			for(j=0;j<5;j++){
				x=x_origin+shape_rotate[i][k][j*2]-x_min;
				y=y_origin+shape_rotate[i][k][j*2+1]-y_min;
				cutline[y][x]=i;
			}
			x_origin=x_origin+x_max+margin_grid+1-x_min;
		}
	}

	//画出格子
	for(i=0;i<n_row;i++){
		for(j=0;j<n_col;j++){
			fill_color = colors[cutline[i][j]]; //选择颜色
			//fill_color=colors[Math.round(Math.random()*11)+1];
            position_x = grid_len* j; //横坐标
            position_y = grid_len*i; //纵坐标
            context.fillStyle = fill_color; //填入颜色
            context.fillRect(position_x, position_y, grid_len- grid_margin,grid_len- grid_margin); //画出格子	
		}
	}

	
}

function getRotateShape(){
	shape_rotate=new Array();
	
	//第1块
	var shape_rotate_row=new Array();
	shape_rotate_row[0]=[0,2,1,2,2,0,2,1,2,2];
	shape_rotate_row[1]=[0,0,1,0,2,0,2,1,2,2];
	shape_rotate_row[2]=[0,0,0,1,0,2,1,0,2,0];
	shape_rotate_row[3]=[0,0,0,1,0,2,1,2,2,2];
	shape_rotate[0]=shape_rotate_row;
	
	//第2块
	var shape_rotate_row=new Array();
	shape_rotate_row[0]=[0,0,0,1,0,2,1,0,1,2];
	shape_rotate_row[1]=[0,0,0,1,1,1,2,0,2,1];
	shape_rotate_row[2]=[0,0,0,1,1,0,2,0,2,1];
	shape_rotate_row[3]=[0,0,0,2,1,0,1,1,1,2];
	shape_rotate[1]=shape_rotate_row;
	
	//第3块
	var shape_rotate_row=new Array();
	shape_rotate_row[0]=[0,0,1,0,1,1,2,0,2,1];
	shape_rotate_row[1]=[0,1,1,0,1,1,2,0,2,1];
	shape_rotate_row[2]=[0,0,0,1,0,2,1,0,1,1];
	shape_rotate_row[3]=[0,0,0,1,0,2,1,1,1,2];
	shape_rotate_row[4]=[0,0,0,1,1,0,1,1,2,1];
	shape_rotate_row[5]=[0,0,0,1,1,0,1,1,2,0];
	shape_rotate_row[6]=[0,1,0,2,1,0,1,1,1,2];
	shape_rotate_row[7]=[0,0,0,1,1,0,1,1,1,2];
	shape_rotate[2]=shape_rotate_row;
	
	//第4块
	var shape_rotate_row=new Array();
	shape_rotate_row[0]=[0,3,1,0,1,1,1,2,1,3];
	shape_rotate_row[1]=[0,0,1,0,1,1,1,2,1,3];
	shape_rotate_row[2]=[0,0,1,0,2,0,3,0,3,1];
	shape_rotate_row[3]=[0,1,1,1,2,1,3,0,3,1];
	shape_rotate_row[4]=[0,0,0,1,0,2,0,3,1,0];
	shape_rotate_row[5]=[0,0,0,1,0,2,0,3,1,3];
	shape_rotate_row[6]=[0,0,0,1,1,1,2,1,3,1];
	shape_rotate_row[7]=[0,0,0,1,1,0,2,0,3,0];
	shape_rotate[3]=shape_rotate_row;
	
	//第5块
	var shape_rotate_row=new Array();
	shape_rotate_row[0]=[0,0,1,0,1,1,2,1,3,1];
	shape_rotate_row[1]=[0,1,1,0,1,1,2,0,3,0];
	shape_rotate_row[2]=[0,2,0,3,1,0,1,1,1,2];
	shape_rotate_row[3]=[0,0,0,1,1,1,1,2,1,3];
	shape_rotate_row[4]=[0,0,1,0,2,0,2,1,3,1];
	shape_rotate_row[5]=[0,1,1,1,2,0,2,1,3,0];
	shape_rotate_row[6]=[0,1,0,2,0,3,1,0,1,1];
	shape_rotate_row[7]=[0,0,0,1,0,2,1,2,1,3];
	shape_rotate[4]=shape_rotate_row;
	
		
	//第6块
	var shape_rotate_row=new Array();
	shape_rotate_row[0]=[0,0,0,1,0,2,0,3,1,1];
	shape_rotate_row[1]=[0,0,0,1,0,2,0,3,1,2];
	shape_rotate_row[2]=[0,1,1,0,1,1,2,1,3,1];
	shape_rotate_row[3]=[0,0,1,0,1,1,2,0,3,0];
	shape_rotate_row[4]=[0,2,1,0,1,1,1,2,1,3];
	shape_rotate_row[5]=[0,1,1,0,1,1,1,2,1,3];
	shape_rotate_row[6]=[0,0,1,0,2,0,2,1,3,0];
	shape_rotate_row[7]=[0,1,1,1,2,0,2,1,3,1];
	shape_rotate[5]=shape_rotate_row;

	//第7块
	var shape_rotate_row=new Array();
	shape_rotate_row[0]=[0,1,1,1,2,0,2,1,2,2];
	shape_rotate_row[1]=[0,0,1,0,1,1,1,2,2,0];
	shape_rotate_row[2]=[0,2,1,0,1,1,1,2,2,2];
	shape_rotate_row[3]=[0,0,0,1,0,2,1,1,2,1];
	shape_rotate[6]=shape_rotate_row;

	//第8块
	var shape_rotate_row=new Array();
	shape_rotate_row[0]=[0,1,1,0,1,1,1,2,2,1];
	shape_rotate[7]=shape_rotate_row;

	//第9块
	var shape_rotate_row=new Array();
	shape_rotate_row[0]=[0,2,1,0,1,1,1,2,2,1];
	shape_rotate_row[1]=[0,0,1,0,1,1,1,2,2,1];
	shape_rotate_row[2]=[0,1,1,0,1,1,2,1,2,2];
	shape_rotate_row[3]=[0,1,1,1,1,2,2,0,2,1];
	shape_rotate_row[4]=[0,1,1,0,1,1,1,2,2,0];
	shape_rotate_row[5]=[0,1,1,0,1,1,1,2,2,2];
	shape_rotate_row[6]=[0,0,0,1,1,1,1,2,2,1];
	shape_rotate_row[7]=[0,1,0,2,1,0,1,1,2,1];
	shape_rotate[8]=shape_rotate_row;

	//第10块
	var shape_rotate_row=new Array();
	shape_rotate_row[0]=[0,0,1,0,2,0,3,0,4,0];
	shape_rotate_row[1]=[0,0,0,1,0,2,0,3,0,4];
	shape_rotate[9]=shape_rotate_row;

	
	//第11块
	var shape_rotate_row=new Array();
	shape_rotate_row[0]=[0,2,1,1,1,2,2,0,2,1];
	shape_rotate_row[1]=[0,0,1,0,1,1,2,1,2,2];
	shape_rotate_row[2]=[0,1,0,2,1,0,1,1,2,0];
	shape_rotate_row[3]=[0,0,0,1,1,1,1,2,2,2];
	shape_rotate[10]=shape_rotate_row;
	
	//第12块
	var shape_rotate_row=new Array();
	shape_rotate_row[0]=[0,2,1,0,1,1,1,2,2,0];
	shape_rotate_row[1]=[0,0,1,0,1,1,1,2,2,2];
	shape_rotate_row[2]=[0,0,0,1,1,1,2,1,2,2];
	shape_rotate_row[3]=[0,1,0,2,1,1,2,0,2,1];
	shape_rotate[11]=shape_rotate_row;
	
	return shape_rotate;

}

function showAllCutline(){
	var cutline_rotate=document.getElementById("cutline_rotate");
	if(cutline_rotate.style.display=="none"){
		document.getElementById("cutline_rotate").style.display="";
	}else{
		document.getElementById("cutline_rotate").style.display="none";
	}
	
}