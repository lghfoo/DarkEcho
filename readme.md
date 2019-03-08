# Dark Echo
## 简介  
> 这是个迷宫游戏。仿照了手游《[回声探路（DarkEcho）](https://baike.baidu.com/item/%E5%9B%9E%E5%A3%B0%E6%8E%A2%E8%B7%AF/16949348?fr=aladdin)》，使用C++和Qt，在PC端上还原这个游戏。游戏的内容和规则与原游戏相似：
## 游戏规则  
* 玩家在一片黑暗通过走动发出声音，从而识别障碍物、陷阱、水域和怪物等
* 玩家移动时发出的声音主要是用白色的线条表示的。线条的转折处表示声音与障碍物发生碰撞。红色的线条表示陷阱，蓝色的线条表示水域
* 玩家总是处于游戏窗口的中心
* 按下鼠标左键时，如果鼠标的位置在玩家附近，那么玩家不会移动，只有释放鼠标时才会发出声音，且声音的大小（也就是线条的数目）与鼠标按下的时间成正比，有上限；如果鼠标的位置不在玩家附近，那么玩家就会朝着鼠标的位置前进，如果从按下到释放鼠标的时间较短，那么玩家就会小步走，发出微小的声音或者不发出声音，如果时间较长，那么玩家就会一直大步走，发出较大的声音。
* 声音会吸引怪物（非水域的地方小步走出的微小声音除外）
* 当玩家走到迷宫的出口后获胜；走到红色的陷阱处会死亡，然后重新开始；走到蓝色的水域，行走的速度会变慢，发出的声音会变大。
## 游戏预览  

开始：  
 ![image](https://github.com/lghfoo/DarkEcho/blob/master/demo/start.gif)  
 
游戏场景1：大步走到出口  
 ![image](https://github.com/lghfoo/DarkEcho/blob/master/demo/scene1.gif)  
 
游戏场景2：躲避陷阱  
 ![image](https://github.com/lghfoo/DarkEcho/blob/master/demo/scene2.gif)  
 
游戏场景3：躲避怪物  
 ![image](https://github.com/lghfoo/DarkEcho/blob/master/demo/scene3.gif)  
 
游戏场景4：水中跋涉  
 ![image](https://github.com/lghfoo/DarkEcho/blob/master/demo/scene4.gif)  
 
游戏场景5：原地跺脚  
 ![image](https://github.com/lghfoo/DarkEcho/blob/master/demo/scene5.gif)  
 
## 代码结构与介绍
<pre>
	<ul>
		<li>目录结构</li>
		<dl>
			<dt>/buttons</dt>
			<dd>这个目录包含了一些自定义按钮。因为这里不方便同时使用Qt的控件和图形，所以按钮都是直接画出来的。按钮主要有文本按钮、图像按钮以及关卡选择按钮，它们都继承自BaseButton。</dd>
			<dt>/images</dt>
			<dd>这个目录包含游戏中的需要用到的图片。目前只有三张，一张表示Qt，一张表示这个游戏的原创作者[Rac7](https://rac7.com/)，最后一张是暂停按钮。</dd>
			<dt>/maps</dt>
			<dd>这个目录包含了所有的游戏地图。</dd>
			<dt>/scenes</dt>
			<dd>
				这个目录下有一个BaseScene基类，以及由它派生出的4个场景类，
				第一个场景ShowScene用来展示一个动画，也就是展示上面提到的前两张图片；
				第二个场景ChoicScene用来给用户选择是否开始游戏。本来一开始打算提供两个选项，一个是开始，一个是观看演示，但后来演示没做，所以只剩下开始选项。
				第三个场景LevelScene用来给用户选择关卡
				第四个场景GameScene就是开始一个关卡后的场景。
			</dd>
			<dt>/walls</dt>
			<dd>这个目录包含了包含了墙壁（也就是障碍物）的定义。一共有两种墙壁，一种是直线墙壁，一种是贝塞尔墙壁，它们都继承自Wall，用来在碰撞发生时计算碰撞结果。</dd>
			<dt>/waves</dt>
			<dd>
				这个目录包含了声音（也就是线条）。游戏中的声音总共有3种。
				第一种声音是ReflectWave，继承自NormalWave，也就是玩家行走时发出的声音，遇到不到的区域可能会有不同的宽度和颜色，而且还会与墙壁发生碰撞，吸引怪物。 
				第二种声音是CustomWave，也继承自NormalWave，会与墙壁发生碰撞，可以自定义颜色与宽度。只有两个地方用到：用来表示怪物的红色线条，开始界面形成DARK ECHO图案的线条。
				第三种声音的CastWave，继承自BaseWave，是玩家扔出石头后，石头发出的声音，只能发生一次碰撞。
			</dd>
			<dt>其他文件</dt>
			<dd>主要有画布、世界、脚印和怪物等。</dd>
		</dl>
		<li>关键类简介</li>
		<dl>
			<dt>Game</dt>
			<dd>负责切换四个场景  </dd>
			<dt>GameScene</dt>
			<dd>游戏的主要场景，负责绝大部分的游戏逻辑，包括与玩家的交互、检测玩家的生死状态、胜利条件、处理玩家与障碍物的碰撞等等。</dd>
			<dt>World</dt>
			<dd>存储地图信息</dd>
			<dt>ReflectWave</dt>
			<dd>最复杂的线条，包含了声音的碰撞逻辑</dd>
			<dt>Canvas</dt>
			<dd>画布，几乎所有的游戏元素都放在这个画布上，可以用来实现特定的效果，比如玩家前进时，脚印向前移动，而画布向相反方向移动，这样就能保持玩家始终在窗口中心；还有关卡选择时，通过移动和缩放画布，来实现移动和缩放全部的关卡选择按钮</dd>
		</dl>
	</ul>
</pre>
## 未完成的内容
* 机关
* 巨型的怪物
* 可移动的障碍物
## 补充
> 游戏中的地图是通过另外一个程序生成的。也就是在另外的程序中绘制地图，然后生成地图文件，再将地图文件放到资源文件中。
