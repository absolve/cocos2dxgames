var res = {
	title_png : "res/title.png",
	start_png : "res/start.png",
	start1_png : "res/start1.png",
	sound_png : "res/sound.png",
	soundOff_png : "res/soundOff.png",
	score_png : "res/score.png",
	cloudBottom_png : "res/cloudBottom.png",
	cloudTop_png : "res/cloudTop.png",
	home_png : "res/home.png",
	help_png : "res/help.png",
	pause_png : "res/pause.png",
	pausePlay_png : "res/pausePlay.png",
	pauseRestart_png : "res/pauseRestart.png",
	scoreDot_png : "res/scoreDot.png",
	colorDot_png : "res/colorDot.png",
	player_png : "res/player.png",
	playerBlink_png : "res/playerBlink.png",
	block_png : "res/blockTop.png",
	blockb_png : "res/blockBottom.png",
	particle_png : "res/particle.png",
	confettiPop_png : "res/confettiPop.png",
	font1_ttf : "res/font1.ttf"
};

var rankname = ['Best round', 'Last round', 'Round played', 'Avg per round', 'Colors earned'];
//颜色容器
var colors = [cc.color(167, 175, 179), cc.color(0, 204, 102), cc.color(96, 98, 128), cc.color(242, 48, 85), cc.color(145, 57, 153), cc.color(255, 102, 51), cc.color(255, 255, 204), cc.color(51, 204, 204), cc.color(255, 204, 51), cc.color(189, 116, 52)];
//游戏的对话
var words = ['Jump on your colors,earn 10 to win!','Tap to jump,again to double jump.'];
var g_resources = [];
for (var i in res) {
	g_resources.push(res[i]);
}
