//游戏开始场景

var welcomeLayer = cc.Layer.extend({
		ctor : function () {
			this._super();
			this.init();
		},
		init : function () {
			//添加背景层
			var bgLayer = new cc.LayerGradient(cc.color(136, 209, 198, 255), cc.color(136, 200, 150, 255), cc.p(0, 1));
			this.addChild(bgLayer);
			//添加云朵1
			this.cloud1 = new cc.Sprite(res.cloudBottom_png);
			this.cloud1.attr({
				x : Math.round(Math.random() * 300) + 200,
				y : Math.round(Math.random() * 220) + 500
			});
			var action1 = new cc.Spawn(new cc.MoveBy(15, cc.p(-640, 0)), new cc.RotateBy(15, -900));
			var action2 = new cc.Sequence(action1, new cc.CallFunc(function () {
						this.cloud1.x = Math.round(Math.random() * 100) + 520;
						this.cloud1.y = Math.round(Math.random() * 320) + 400;
					}, this));
			this.cloud1.runAction(new cc.RepeatForever(action2));
			//添加云朵2
			this.cloud2 = new cc.Sprite(res.cloudBottom_png);
			this.cloud2.attr({
				x : Math.round(Math.random() * 200) + 300,
				y : Math.round(Math.random() * 100) + 400
			});
			var action3 = new cc.Spawn(new cc.MoveBy(17, cc.p(-640, 0)), new cc.RotateBy(17, 900));
			var action4 = new cc.Sequence(action3, new cc.CallFunc(function () {
						this.cloud2.x = Math.round(Math.random() * 100) + 520;
						this.cloud2.y = Math.round(Math.random() * 100) + 400;
					}, this));
			this.cloud2.runAction(new cc.RepeatForever(action4));

			bgLayer.addChild(this.cloud1);
			bgLayer.addChild(this.cloud2);
			//添加标志
			this.logo = new cc.Sprite(res.title_png);
			this.logo.attr({
				x : cc.winSize.width / 2,
				y : 600
			});
			this.addChild(this.logo);
			//添加开始按钮
			this.startBtn = new cc.MenuItemImage(res.start_png, res.start1_png, this.startBtnCB, this);
			this.startBtn.attr({
				x : cc.winSize.width / 2,
				y : 400
			});
			//添加游戏继续按钮
			this.resumeBtn = new cc.MenuItemImage(res.pausePlay_png, res.pausePlay_png, this.resumeCB, this);
			this.resumeBtn.attr({
				x : 240,
				y : -80
			});
			//添加游戏重新开始
			this.restartBtn = new cc.MenuItemImage(res.pauseRestart_png, res.pauseRestart_png, this.restartCB, this);
			this.restartBtn.attr({
				x : 520,
				y : 400
			});
			//添加声音按钮
			this.soundBtn = new cc.MenuItemImage(res.sound_png, res.soundOff_png, this.soundBtnCB, this);
			this.soundBtn.attr({
				x : 50,
				y : 50
			});
			//添加排行版按钮
			this.rankBtn = new cc.MenuItemImage(res.score_png, res.score_png, this.rankBtnCB, this);
			this.rankBtn.attr({
				x : 440,
				y : 50
			});
			//添加返回主界面按钮
			this.homeBtn = new cc.MenuItemImage(res.home_png, res.home_png, this.returnHomeAni, this);
			this.homeBtn.attr({
				x : 50,
				y : -50
			});
			//帮助按钮
			this.helpBtn = new cc.MenuItemImage(res.help_png, res.help_png, this.helpAni, this);
			this.helpBtn.attr({
				x : 350,
				y : 300
			});
			//添加暂停按钮
			this.pauseBtn = new cc.MenuItemImage(res.pause_png, res.pause_png, this.pauseAni, this);
			this.pauseBtn.attr({
				x : 440,
				y : 680
			});
			this.pauseBtn.setVisible(false);
			//添加菜单
			var menu1 = new cc.Menu(this.startBtn, this.soundBtn, this.rankBtn, this.homeBtn, this.helpBtn, this.pauseBtn, this.resumeBtn, this.restartBtn);
			menu1.x = 0;
			menu1.y = 0;
			this.addChild(menu1, 2);
			//添加游戏的帮助字符串
			this.helpWord1 = new cc.LabelTTF(words[0], 'Arial', 25);
			this.helpWord1.attr({
				x : 240,
				y : 450
			});
			this.helpWord1.setVisible(false);
			this.addChild(this.helpWord1);
			this.helpWord2 = new cc.LabelTTF(words[1], 'Arial', 25);
			this.helpWord2.attr({
				x : 210,
				y : 200
			});
			this.helpWord2.setVisible(false);
			this.addChild(this.helpWord2);

			//添加音乐开关
			this.soundoff = false;
			//数据读取
			this.readData();
			this.addScoreUI();
			//添加动画状态
			this.helpState = false;
			this.rankState = false;
			//添加游戏状态
			this.gidle = true;
			this.gstart = false;
			this.gpause = false;
			this.gend = false;
			//添加玩家
			this._player = new player(res.player_png);
			this._player.attr({
				x : 100,
				y : 340
			});
			this.addChild(this._player, 2);
			//添加定时器
			this.scheduleUpdate();
			//添加事件
			this.addEventEventListener();
			//烟火的容器
			this.fireArray = [];
			//方块数组 存储所有的方块
			this.blockArray = [];
			//添加颜色数组打乱顺序的数组
			this.colorArray = new Array(10);
			//已获取游戏的颜色
			this.getCArray = [];
			//未获取的颜色
			this.needCArray = [];
			//当前获取的颜色方块数
			this.getBlockNum = 0;
			//所有的颜色点
			this.getColorArray = [];
			//游戏的时间
			this.time = 0.0;
			//胜利条件
			this.win = false;
			//游戏正式进行标志
			this.runFlag = false;
			//游戏结束并返回的标志
			this.endAndIdle = false;
			//游戏初始化的颜色数组
			this.initColorArray();
			//创建开始的方块
			for (var i = 0; i <= 4; i++) {
				this.addBlock(this.getCArray[0], cc.p(-10 + i * 100, -100), true);
			}
			this.colorDot();

		},
		//碰撞检测
		collision_detection : function () {
			var rect1 = this._player.getBoundingBox();
			var nflag = true;
			for (var i in this.blockArray) {
				var rect2 = this.blockArray[i].getBoundingBox();
				rect2.x += 20;
				rect2.height -= 18;
				rect2.width -= 38;
				//判断是否碰撞
				if (rect1.x + rect1.width >= rect2.x && rect2.x + rect2.width >= rect1.x && rect1.y + rect1.height >= rect2.y && rect2.y + rect2.height >= rect1.y) {
					if (this.blockArray[i].allowStand === true) {
						if (rect2.y + rect2.height <= rect1.y + 13) {
							//判断是否正在跳跃阶段
							if (this._player.speed <= 0) {
								this._player.speed = 0;
								this._player._jump = 0;
								nflag = false;
							}
						} else {
							this._player.x -= 2.5;
						}
					}
				}
			}
			this._player.flag = nflag;
		},
		//更新函数
		update : function (dt) {
			//根据游戏状态更新
			if (this.gidle) {
				for (var i in this.blockArray) {
					this.blockArray[i].x = this.blockArray[i].x - 2;
				}
				//适当的添加方块
				if (this.blockArray[this.blockArray.length - 1].x < 380) {
					//添加方块
					this.addBlock(this.getCArray[0], cc.p(480, -100), true);
				}
				//清除超过屏幕的方块
				for (var i in this.blockArray) {
					if (this.blockArray[i].x < -120) {
						this.blockArray[i].removeFromParent();
						this.blockArray.splice(i, 1);
					}
				}
				//碰撞检测
				this.collision_detection();
				//更新玩家
				this._player.update(dt);
			} else if (this.gstart) {
				//游戏时间增加
				this.time += dt;
				//移动方块
				for (var i in this.blockArray) {
					this.blockArray[i].x = this.blockArray[i].x - 2.5;
				}
				//更新玩家
				this._player.update(dt);
				//碰撞检测
				this.collision_detection();
				//如果玩家已获胜
				if (this.win == true) {
					this.runFlag = false;
					this.gend = true;
					this.gstart = false;
					//添加烟火
					this.firework(cc.p(200, -200), cc.p(200, 500));
					var that = this;
					this.runAction(new cc.Sequence(new cc.DelayTime(4), new cc.CallFunc(function () {
								this.endAndIdle = true;
								this.win = false;
							}, that)));
					return;
				}
				//如果没次跳过15个方块就添加一个方块
				if (Math.floor(this.getBlockNum / 15) > this.getCArray.length) {
					//从未获取的方块中弹出一个
					var color = this.needCArray.shift();
					this.getCArray.push(color);
					this.addGetColorDot(color);
				}
				//添加方块
				if (this.runFlag) {
					if (this.needCArray.length == 0) {
						this.win = true;
						return;
					}
					//适当的添加方块
					if (this.blockArray[this.blockArray.length - 1].x < 380) {
						//判断最后一个方块是否可踩
						if (this.blockArray[this.blockArray.length - 1].allowStand) {
							var num = Math.floor(Math.random() * this.needCArray.length);
							this.addBlock(this.needCArray[num], cc.p(480, -100 + Math.round(Math.random() * 100)), false);
						} else if (!this.blockArray[this.blockArray.length - 1].allowStand && this.blockArray[this.blockArray.length - 2].allowStand) {
							//随机70%的概率再添加一个不可踩的方块
							var ok = Math.random() > 0.7 ? true : false;
							if (ok) {
								var num = Math.floor(Math.random() * this.needCArray.length);
								this.addBlock(this.needCArray[num], cc.p(480, -100 + Math.round(Math.random() * 100)), false);
							} else {
								var num = Math.floor(Math.random() * this.getCArray.length);
								this.addBlock(this.getCArray[num], cc.p(480, -100 + Math.round(Math.random() * 100)), true);
							}
						} else {
							//添加一个可踩的方块
							var num = Math.floor(Math.random() * this.getCArray.length);
							this.addBlock(this.getCArray[num], cc.p(480, -100 + Math.round(Math.random() * 100)), true);
						}
					}
				} else {
					//适当的添加方块
					if (this.blockArray[this.blockArray.length - 1].x < 380) {
						//添加方块
						this.addBlock(this.getCArray[0], cc.p(480, -100), true);
					}
				}
				//清除超过屏幕的方块并记录获取的方块数
				for (var i in this.blockArray) {
					if (this.blockArray[i].x < -120) {
						this.blockArray[i].removeFromParent();
						this.blockArray.splice(i, 1);
						//如果正式开始对跳过的方块进行计数
						if (this.runFlag) {
							this.getBlockNum++;
						}
					}
				}
				//判断角色是否死亡
				if (this._player.dead) {
					this.gstart = false;
					this.gend = true;
					this.firework(cc.p(200, -10), cc.p(200, 500));
					for (var i in this.blockArray) {
						this.blockArray[i].runAction(new cc.MoveBy(5, cc.p(0, -50)));
					}
					var that = this;
					this.runAction(new cc.Sequence(new cc.DelayTime(3.5), new cc.CallFunc(function () {
								this.endAndIdle = true;
							}, that)));
				}
			} else if (this.gend) {
				if (this.endAndIdle) {
					//得分处理
					if (this.getCArray.length > parseInt(this.num[0])) {
						cc.sys.localStorage.setItem(rankname[0], this.getCArray.length);
						this.num[0] = this.getCArray.length;
					}
					cc.sys.localStorage.setItem(rankname[1], this.getCArray.length);
					this.num[2]++;
					var ptime = this.getBlockNum / this.time;
					this.num[3] = ptime.toFixed(2);
					cc.sys.localStorage.setItem(rankname[3], this.num[3]);
					cc.sys.localStorage.setItem(rankname[2], this.num[2]);
					this.num[4] += this.getCArray.length;
					cc.sys.localStorage.setItem(rankname[4], this.num[4]);

					//游戏时间清除
					this.time = 0.0;
					//获取的方块数清零
					this.getBlockNum = 0;
					//清空所有颜色数组
					this.colorArray.splice(0, this.colorArray.length);
					//获取的颜色数组清空
					this.getCArray.splice(0, this.getCArray.length);
					//未获取的颜色数组清空
					this.needCArray.splice(0, this.needCArray.length);
					//清除所有获取颜色
					for (var i in this.getColorArray) {
						this.getColorArray[i].removeFromParent();
					}
					this.getColorArray.splice(0, this.getColorArray.length);
					this.initColorArray();
					//重新设置玩家
					this._player.attr({
						x : 100,
						y : 200
					});
					this._player.dead = false;
					this._player.speed = 0;

					//状态恢复
					this.gend = false;
					this.gidle = true;
					this.endAndIdle = false;
					//将界面恢复
					this.pauseBtn.setEnabled(true);
					this.pauseBtn.setVisible(false);
					//将logo隐藏
					this.logo.runAction(new cc.MoveBy(0.3, cc.p(0, -300)));
					//将按钮隐藏
					this.startBtn.runAction(new cc.MoveBy(0.3, cc.p(320, 0)));
					this.soundBtn.runAction(new cc.MoveBy(0.3, cc.p(0, 100)));
					this.rankBtn.runAction(new cc.MoveBy(0.3, cc.p(-80, 0)));
					this.helpBtn.runAction(new cc.MoveBy(0.3, cc.p(-300, 0)));
					//清理烟花
					for (var i in this.fireArray) {
						this.fireArray[i].removeFromParent();
					}
					this.fireArray.splice(0, this.fireArray.length);
					//重新添加台阶
					for (var i in this.blockArray) {
						this.blockArray[i].removeFromParent();
					}
					this.blockArray.splice(0, this.blockArray.length);
					//创建开始的方块
					for (var i = 0; i <= 4; i++) {
						this.addBlock(this.getCArray[0], cc.p(-10 + i * 100, -100), true);
					}
					//添加一个延迟
					this.runFlag = false;
					//分数点显示动画
					for (var i = 0; i < 10; i++) {
						this.colorDots[i].runAction(new cc.MoveBy(0.1 + i * 0.06, cc.p(-380, 0)));
					}
				}
			} else if (this.gpause) {}
		},
		//添加以获取颜色点
		addGetColorDot : function (color) {
			var spr1 = new cc.Sprite(res.colorDot_png);
			//判断获取的颜色跳过5个
			if (this.getColorArray.length < 5) {
				spr1.attr({
					x : 530,
					y : 600
				});
				var s = 400 - this.getColorArray.length * 55;
				spr1.runAction(new cc.EaseBounceOut(new cc.MoveBy(0.7, cc.p(-s, 0))));
			} else {
				spr1.attr({
					x : 530,
					y : 550
				});
				var s = 400 - (this.getColorArray.length - 5) * 55;
				spr1.runAction(new cc.EaseBounceOut(new cc.MoveBy(0.7, cc.p(-s, 0))));
			}
			spr1.setColor(color);
			this.getColorArray.push(spr1);
			this.addChild(spr1);
		},
		//初始化颜色数组
		initColorArray : function () {
			for (var i in colors) {
				this.colorArray[i] = colors[i];
			}
			//打乱数组
			this.colorArray.sort(function () {
				return Math.random() > 0.5 ? -1 : 1;
			});
			this.getCArray.push(this.colorArray[0]);
			for (var i = 1; i < 10; i++) {
				this.needCArray.push(this.colorArray[i]);
			}
		},
		//添加方块
		addBlock : function (color, point, allowStand) {
			var block1 = new block(res.block_png);
			block1.init(color, allowStand);
			block1.attr({
				x : point.x,
				y : point.y,
				anchorX : 0,
				anchorY : 0
			});
			this.blockArray.push(block1);
			this.addChild(block1);
		},
		//烟花效果
		firework : function (point1, point2) {
			for (var i = 0; i < 40; i++) {
				var sp = new cc.Sprite(res.scoreDot_png);
				sp.attr({
					x : point1.x,
					y : point1.y,

				});
				//设置随机颜色
				sp.setColor(cc.color(Math.round(Math.random() * 255), Math.round(Math.random() * 255), Math.round(Math.random() * 255)));
				//设置精灵的动作
				var fire = new cc.MoveTo(1, cc.p(point2.x - 80 + Math.round(Math.random() * 160), point2.y - 150 + Math.round(Math.random() * 300)));
				//下落
				var downRotate = new cc.MoveBy(10, cc.p(0, -150));
				sp.runAction(new cc.Sequence(new cc.EaseExponentialOut(fire), downRotate));
				this.addChild(sp, 3);
				this.fireArray.push(sp);
			}
		},
		//添加得到的颜色点
		colorDot : function () {
			this.colorDots = new Array(10);
			for (var i = 0; i < 10; i++) {
				this.colorDots[i] = new cc.Sprite(res.scoreDot_png);
				this.colorDots[i].attr({
					x : 510 + i * 25,
					y : 500
				});
				this.addChild(this.colorDots[i]);
			}
			for (var i = 0; i < 10; i++) {
				this.colorDots[i].runAction(new cc.MoveBy(0.1 + i * 0.06, cc.p(-380, 0)));
			}
		},
		//事件处理函数
		addEventEventListener : function () {
			if (cc.sys.platform === cc.sys.DESKTOP_BROWSER) {
				var that = this;
				var listener = cc.EventListener.create({
						event : cc.EventListener.KEYBOARD,
						onKeyPressed : function (key, event) {
							//cc.log("Key down:" + key);
							if (key == 32) {
								that.keyDown();
							}
						},
						onKeyReleased : function (key, event) {
							//cc.log("Key up:" + key);
						}
					});
				cc.eventManager.addListener(listener, this);
			} else if (cc.sys.platform === cc.sys.ANDROID) {
				var that = this;
				cc.eventManager.addListener({
					event : cc.EventListener.TOUCH_ONE_BY_ONE,
					swallowTouches : true,
					onTouchBegan : function (touch, event) {
						that.keyDown();
					}
				}, this);
				//在安卓上添加退出事件
				// cc.eventManager.addListener({
				// event : cc.EventListener.KEYBOARD,
				// onKeyReleased : function (keyCode, event) {

				// cc.director.purgeDirector();

				// }
				// }, this);
			}
		},
		//键盘/触摸事件
		keyDown : function () {
			if (this.gstart) {
				this._player.jump();
			}
		},
		//读取数据
		readData : function () {
			if (cc.sys.platform === cc.sys.DESKTOP_BROWSER) {
				//判断是否第一次运行
				if (cc.sys.localStorage.getItem('Best round') == null) {
					//初始化数据
					cc.sys.localStorage.setItem('Best round', 0);
					cc.sys.localStorage.setItem('Last round', 0);
					cc.sys.localStorage.setItem('Round played', 0);
					cc.sys.localStorage.setItem('Avg per round', 0);
					cc.sys.localStorage.setItem('Colors earned', 0);
				}
				this.num = new Array(5);
				this.num[0] = parseInt(cc.sys.localStorage.getItem('Best round'));
				this.num[1] = parseInt(cc.sys.localStorage.getItem('Last round'));
				this.num[2] = parseInt(cc.sys.localStorage.getItem('Round played'));
				this.num[3] = parseFloat(cc.sys.localStorage.getItem('Avg per round'))
					this.num[4] = parseInt(cc.sys.localStorage.getItem('Colors earned'));
			} else if (cc.sys.platform === cc.sys.ANDROID) {
				//判断是否第一次运行
				if (cc.sys.localStorage.getItem('Best round') == 0) {
					//初始化数据
					cc.sys.localStorage.setItem('Best round', 0);
					cc.sys.localStorage.setItem('Last round', 0);
					cc.sys.localStorage.setItem('Round played', 0);
					cc.sys.localStorage.setItem('Avg per round', 0);
					cc.sys.localStorage.setItem('Colors earned', 0);
				}
				this.num = new Array(5);
				this.num[0] = parseInt(cc.sys.localStorage.getItem('Best round'));
				this.num[1] = parseInt(cc.sys.localStorage.getItem('Last round'));
				this.num[2] = parseInt(cc.sys.localStorage.getItem('Round played'));
				this.num[3] = parseFloat(cc.sys.localStorage.getItem('Avg per round'))
					this.num[4] = parseInt(cc.sys.localStorage.getItem('Colors earned'));
			}
		},
		//添加得分按钮
		addScoreUI : function () {
			//添加排行榜信息
			this.labelstr = new Array(5);
			for (var i = 0; i <= 1; i++) {
				this.labelstr[i] = new cc.LabelTTF(rankname[i], 'Arial', 25);
				this.labelstr[i].attr({
					x : -155,
					y : 500 - i * 40,
					anchorX : 0,
					textAlign : cc.TEXT_ALIGNMENT_RIGHT
				});
				this.addChild(this.labelstr[i]);
			}

			for (var i = 2; i <= 4; i++) {
				this.labelstr[i] = new cc.LabelTTF(rankname[i], 'Arial', 25);
				this.labelstr[i].attr({
					x : -155,
					y : 420 - (i - 2) * 40,
					anchorX : 0,
					textAlign : cc.TEXT_ALIGNMENT_RIGHT
				});
				this.addChild(this.labelstr[i]);
			}
			//添加分数字符串
			this.labelnum = new Array(5);
			for (var i = 0; i < 5; i++) {
				this.labelnum[i] = new cc.LabelTTF(this.num[i], 'Arial', 25);
				this.labelnum[i].attr({
					x : 500,
					y : 500 - i * 40,
					anchorX : 0
				});
				this.labelnum[i].setColor(cc.color(248, 98, 125));
				this.addChild(this.labelnum[i]);
			}
		},
		//开始按钮回调函数
		startBtnCB : function () {
			this.gidle = false;
			this.gstart = true;
			this.gameStartAni();
			this.pauseBtn.setEnabled(false);
			//添加一个延迟动作
			var that = this;
			this.runAction(new cc.Sequence(new cc.DelayTime(1.5), new cc.CallFunc(function () {
						this.runFlag = true;
						this.pauseBtn.setEnabled(true);
						//添加获取的颜色点
						this.addGetColorDot(this.getCArray[0]);
					}, that)));
		},
		//游戏继续回调函数
		resumeCB : function () {
			this.pauseBtn.setEnabled(true);
			this.resumeBtn.runAction(new cc.MoveBy(0.5, cc.p(0, -480)));
			this.restartBtn.runAction(new cc.MoveBy(0.5, cc.p(200, 0)));
			this.homeBtn.runAction(new cc.MoveBy(0.5, cc.p(-110, -450)));
			//设置标志
			this.gstart = true;
			this.gpause = false;
		},
		//游戏重新开始回调函数
		restartCB : function () {
			//将logo恢复
			this.logo.runAction(new cc.MoveBy(0.3, cc.p(0, -300)));
			//将按钮隐藏
			this.startBtn.runAction(new cc.MoveBy(0.3, cc.p(320, 0)));
			this.soundBtn.runAction(new cc.MoveBy(0.3, cc.p(0, 100)));
			this.rankBtn.runAction(new cc.MoveBy(0.3, cc.p(-80, 0)));
			this.helpBtn.runAction(new cc.MoveBy(0.3, cc.p(-300, 0)));
			this.pauseBtn.setEnabled(true);
			this.pauseBtn.setVisible(false);
			this.homeBtn.runAction(new cc.MoveBy(0.2, cc.p(-110, -450)));
			this.resumeBtn.runAction(new cc.MoveBy(0.2, cc.p(0, -480)));
			this.restartBtn.runAction(new cc.MoveBy(0.2, cc.p(200, 0)));
			// //分数点显示动画
			for (var i = 0; i < 10; i++) {
				this.colorDots[i].runAction(new cc.MoveBy(0.1 + i * 0.06, cc.p(-380, 0)));
			}
			this.gpause = false;
			//游戏时间清除
			this.time = 0.0;
			//获取的方块数清零
			this.getBlockNum = 0;
			//清空所有颜色数组
			this.colorArray.splice(0, this.colorArray.length);
			//获取的颜色数组清空
			this.getCArray.splice(0, this.getCArray.length);
			//未获取的颜色数组清空
			this.needCArray.splice(0, this.needCArray.length);
			//清除所有获取颜色
			for (var i in this.getColorArray) {
				this.getColorArray[i].removeFromParent();
			}
			this.getColorArray.splice(0, this.getColorArray.length);
			this.initColorArray();
			//重新设置玩家
			this._player.attr({
				x : 100,
				y : 200
			});
			this._player.dead = false;
			this._player.speed = 0;

			//状态恢复
			this.gidle = true;
			//将界面恢复
			this.pauseBtn.setEnabled(true);
			this.pauseBtn.setVisible(false);
			//清理烟花
			for (var i in this.fireArray) {
				this.fireArray[i].removeFromParent();
			}
			this.fireArray.splice(0, this.fireArray.length);
			//重新添加台阶
			for (var i in this.blockArray) {
				this.blockArray[i].removeFromParent();
			}
			this.blockArray.splice(0, this.blockArray.length);
			//创建开始的方块
			for (var i = 0; i <= 4; i++) {
				this.addBlock(this.getCArray[0], cc.p(-10 + i * 100, -100), true);
			}
			//添加一个延迟
			this.runFlag = false;
		},
		//游戏暂停动画
		pauseAni : function () {
			if (this.gend) {
				return;
			}
			//设置游戏暂停标志
			this.gstart = false;
			this.gpause = true;
			this.pauseBtn.setEnabled(false);
			this.resumeBtn.runAction(new cc.MoveBy(0.5, cc.p(0, 480)));
			this.restartBtn.runAction(new cc.MoveBy(0.5, cc.p(-200, 0)));
			this.homeBtn.runAction(new cc.MoveBy(0.5, cc.p(110, 450)));

		},
		//声音按钮回调函数
		soundBtnCB : function () {
			this.soundoff = !this.soundoff;
			if (this.soundoff === true) {
				this.soundBtn.setNormalSpriteFrame(new cc.SpriteFrame(res.soundOff_png, cc.rect(0, 0, 80, 80)));
			} else {
				this.soundBtn.setNormalSpriteFrame(new cc.SpriteFrame(res.sound_png, cc.rect(0, 0, 80, 80)));
			}
		},
		//排行版按钮回调函数
		rankBtnCB : function () {
			this.rankAni();
		},
		//游戏开始动画
		gameStartAni : function () {
			//将logo隐藏
			this.logo.runAction(new cc.MoveBy(0.3, cc.p(0, 300)));
			//将按钮隐藏
			this.startBtn.runAction(new cc.MoveBy(0.3, cc.p(-320, 0)));
			this.soundBtn.runAction(new cc.MoveBy(0.3, cc.p(0, -100)));
			this.rankBtn.runAction(new cc.MoveBy(0.3, cc.p(80, 0)));
			this.helpBtn.runAction(new cc.MoveBy(0.3, cc.p(300, 0)));
			this.pauseBtn.setVisible(true);
			//隐藏分数点
			for (var i = 0; i < 10; i++) {
				this.colorDots[i].x = 510 + i * 25;
			}
		},
		//排行榜动画
		rankAni : function () {
			this.gameStartAni();
			this.homeBtn.runAction(new cc.MoveBy(0.3, cc.p(0, 100)));
			this.pauseBtn.setVisible(false);
			//字符串动画
			for (var i = 0; i <= 1; i++) {
				this.labelstr[i].runAction(new cc.MoveBy(0.3, cc.p(310, 0)));
			}
			for (var i = 2; i <= 4; i++) {
				this.labelstr[i].runAction(new cc.MoveBy(0.3, cc.p(270, 0)));
			}
			for (var i in this.labelnum) {
				this.labelnum[i].setString(this.num[i]);
				this.labelnum[i].runAction(new cc.MoveBy(0.3, cc.p(-200, 0)))
			}
			this.rankState = true;
		},
		//返回主界面动画
		returnHomeAni : function () {
			//将logo恢复
			this.logo.runAction(new cc.MoveBy(0.3, cc.p(0, -300)));
			//将按钮隐藏
			this.startBtn.runAction(new cc.MoveBy(0.3, cc.p(320, 0)));
			this.soundBtn.runAction(new cc.MoveBy(0.3, cc.p(0, 100)));
			this.rankBtn.runAction(new cc.MoveBy(0.3, cc.p(-80, 0)));
			this.helpBtn.runAction(new cc.MoveBy(0.3, cc.p(-300, 0)));

			if (this.rankState) {
				this.homeBtn.runAction(new cc.MoveBy(0.3, cc.p(0, -100)));
				//字符串隐藏动画
				for (var i = 0; i <= 1; i++) {
					this.labelstr[i].runAction(new cc.MoveBy(0.3, cc.p(-310, 0)));
				}
				for (var i = 2; i <= 4; i++) {
					this.labelstr[i].runAction(new cc.MoveBy(0.3, cc.p(-270, 0)));
				}
				for (var i in this.labelnum) {
					this.labelnum[i].runAction(new cc.MoveBy(0.3, cc.p(200, 0)))
				}
				//分数点显示动画
				for (var i = 0; i < 10; i++) {
					this.colorDots[i].runAction(new cc.MoveBy(0.1 + i * 0.06, cc.p(-380, 0)));
				}
				this.rankState = false;
			} else if (this.helpState) {
				this.homeBtn.runAction(new cc.MoveBy(0.3, cc.p(0, -100)));
				//分数点显示动画
				for (var i = 0; i < 10; i++) {
					this.colorDots[i].runAction(new cc.MoveBy(0.1 + i * 0.06, cc.p(-380, 0)));
				}
				this.helpState = false;
				//隐藏字符串
				this.helpWord1.setVisible(false);
				this.helpWord2.setVisible(false);
				//清除所有获取颜色
				for (var i in this.getColorArray) {
					this.getColorArray[i].removeFromParent();
				}
				this.getColorArray.splice(0, this.getColorArray.length);

			} else if (this.gpause) {
				this.pauseBtn.setEnabled(true);
				this.pauseBtn.setVisible(false);
				this.homeBtn.runAction(new cc.MoveBy(0.2, cc.p(-110, -450)));
				this.resumeBtn.runAction(new cc.MoveBy(0.2, cc.p(0, -480)));
				this.restartBtn.runAction(new cc.MoveBy(0.2, cc.p(200, 0)));
				// //分数点显示动画
				for (var i = 0; i < 10; i++) {
					this.colorDots[i].runAction(new cc.MoveBy(0.1 + i * 0.06, cc.p(-380, 0)));
				}
				this.gpause = false;

				//获取的方块数清零
				this.getBlockNum = 0;
				//清空所有颜色数组
				this.colorArray.splice(0, this.colorArray.length);
				//获取的颜色数组清空
				this.getCArray.splice(0, this.getCArray.length);
				//未获取的颜色数组清空
				this.needCArray.splice(0, this.needCArray.length);
				//清除所有获取颜色
				for (var i in this.getColorArray) {
					this.getColorArray[i].removeFromParent();
				}
				this.getColorArray.splice(0, this.getColorArray.length);
				this.initColorArray();
				//重新设置玩家
				this._player.attr({
					x : 100,
					y : 200
				});
				this._player.dead = false;
				this._player.speed = 0;
				//清除游戏时间
				this.time = 0.0;
				//状态恢复
				this.gidle = true;
				//将界面恢复
				this.pauseBtn.setEnabled(true);
				this.pauseBtn.setVisible(false);
				//清理烟花
				for (var i in this.fireArray) {
					this.fireArray[i].removeFromParent();
				}
				this.fireArray.splice(0, this.fireArray.length);
				//重新添加台阶
				for (var i in this.blockArray) {
					this.blockArray[i].removeFromParent();
				}
				this.blockArray.splice(0, this.blockArray.length);
				//创建开始的方块
				for (var i = 0; i <= 4; i++) {
					this.addBlock(this.getCArray[0], cc.p(-10 + i * 100, -100), true);
				}
				//添加一个延迟
				this.runFlag = false;
			} else {
				this.homeBtn.runAction(new cc.MoveBy(0.3, cc.p(0, -100)));
				//分数点显示动画
				for (var i = 0; i < 10; i++) {
					this.colorDots[i].runAction(new cc.MoveBy(0.1 + i * 0.06, cc.p(-380, 0)));
				}
			}
		},
		//帮助动画界面
		helpAni : function () {
			this.gameStartAni();
			this.homeBtn.runAction(new cc.MoveBy(0.3, cc.p(0, 100)));
			this.pauseBtn.setVisible(false);
			this.helpState = true;

			//添加字符串
			this.helpWord1.setVisible(true);
			this.helpWord2.setVisible(true);
			//添加颜色球
			for (var i = 0; i < 3; i++) {
				this.addGetColorDot(this.colorArray[i]);
			}
		}
	});

//方块类
var block = cc.Sprite.extend({
		ctor : function (fileName, rect, rotated) {
			this._super(fileName, rect, rotated);
			// this.color = cc.color(255, 255, 255);
			//设置是否可以站立
			this.allowStand = false;
		},
		init : function (_color, _allowStand) {
			this.setColor(_color);
			this.allowStand = _allowStand;
		}
	});
//选手类
var player = cc.Sprite.extend({
		ctor : function (fileName, rect, rotated) {
			this._super(fileName, rect, rotated);
			this.anchorX = 0;
			this.anchorY = 0;
			//设置是否死亡
			this.dead = false;
			//跳跃次数
			this._jump = 0;
			//加速度
			this.aspeed = -560;
			//速度
			this.speed = 0.0;
			//重力开关
			this.flag = true;
		},
		//更新函数
		update : function (dt) {
			//判断死亡状态
			if (this.dead) {
				return;
			}
			if (this.flag == true) {
				if (this._jump > 0) {
					this.speed = this.speed + this.aspeed * dt;
					this.y = this.y + this.speed * dt + this.aspeed * dt * dt / 2;
				} else {
					this.speed = this.speed + this.aspeed * dt;
					this.y = this.y + this.speed * dt + this.aspeed * dt * dt / 2;
				}
				if (this.y < -50 || this.x < -50) {
					this.dead = true;
				}
			}
		},
		//跳跃
		jump : function () {
			//判断跳跃的次数
			if (this._jump < 2) {
				this.flag = true;
				this._jump++;
				this.speed = 300;
			}
		}
	});

var welcomeScene = cc.Scene.extend({
		onEnter : function () {
			this._super();
			var layer1 = new welcomeLayer();
			this.addChild(layer1);
		}
	});
