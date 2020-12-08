<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile doxygen_version="1.9.0" doxygen_gitid="a5ac10888f6c0b0fc00678f67aa49036b33aa4cf">
  <compound kind="file">
    <name>Controls.h</name>
    <path>/home/jero/projects/proyecto_final/oop-project/</path>
    <filename>Controls_8h.html</filename>
    <class kind="class">Controls</class>
  </compound>
  <compound kind="file">
    <name>Entity.h</name>
    <path>/home/jero/projects/proyecto_final/oop-project/</path>
    <filename>Entity_8h.html</filename>
    <class kind="class">Entity</class>
  </compound>
  <compound kind="file">
    <name>Game.h</name>
    <path>/home/jero/projects/proyecto_final/oop-project/</path>
    <filename>Game_8h.html</filename>
    <includes id="Scene_8h" name="Scene.h" local="yes" imported="no">Scene.h</includes>
    <includes id="Menu_8h" name="Menu.h" local="yes" imported="no">Menu.h</includes>
    <includes id="Match_8h" name="Match.h" local="yes" imported="no">Match.h</includes>
    <includes id="Settings_8h" name="Settings.h" local="yes" imported="no">Settings.h</includes>
    <class kind="class">Game</class>
  </compound>
  <compound kind="file">
    <name>Item.h</name>
    <path>/home/jero/projects/proyecto_final/oop-project/</path>
    <filename>Item_8h.html</filename>
    <includes id="Entity_8h" name="Entity.h" local="yes" imported="no">Entity.h</includes>
    <class kind="class">Item</class>
  </compound>
  <compound kind="file">
    <name>main.cpp</name>
    <path>/home/jero/projects/proyecto_final/oop-project/</path>
    <filename>main_8cpp.html</filename>
    <includes id="Game_8h" name="Game.h" local="yes" imported="no">Game.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>LOVIGAME</name>
      <anchorfile>main_8cpp.html</anchorfile>
      <anchor>a2cb75272d629b0a8e788e4270bd39f06</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchorfile>main_8cpp.html</anchorfile>
      <anchor>a0ddf1224851353fc92bfbff6f499fa97</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Match.h</name>
    <path>/home/jero/projects/proyecto_final/oop-project/</path>
    <filename>Match_8h.html</filename>
    <includes id="Menu_8h" name="Menu.h" local="yes" imported="no">Menu.h</includes>
    <includes id="Scene_8h" name="Scene.h" local="yes" imported="no">Scene.h</includes>
    <includes id="Player_8h" name="Player.h" local="yes" imported="no">Player.h</includes>
    <includes id="World_8h" name="World.h" local="yes" imported="no">World.h</includes>
    <class kind="class">Match</class>
  </compound>
  <compound kind="file">
    <name>Menu.h</name>
    <path>/home/jero/projects/proyecto_final/oop-project/</path>
    <filename>Menu_8h.html</filename>
    <includes id="Scene_8h" name="Scene.h" local="yes" imported="no">Scene.h</includes>
    <includes id="Match_8h" name="Match.h" local="yes" imported="no">Match.h</includes>
    <includes id="Controls_8h" name="Controls.h" local="yes" imported="no">Controls.h</includes>
    <class kind="class">Menu</class>
  </compound>
  <compound kind="file">
    <name>phutils.h</name>
    <path>/home/jero/projects/proyecto_final/oop-project/</path>
    <filename>phutils_8h.html</filename>
    <class kind="class">utils::HSV</class>
    <namespace>utils</namespace>
    <member kind="function">
      <type>HSV</type>
      <name>MakeHSV</name>
      <anchorfile>namespaceutils.html</anchorfile>
      <anchor>a74fcd67e4f22f40a83e7dc52f1b1fdbe</anchor>
      <arglist>(const sf::Color &amp;rgb)</arglist>
    </member>
    <member kind="function">
      <type>sf::Vector2f</type>
      <name>getCenter</name>
      <anchorfile>namespaceutils.html</anchorfile>
      <anchor>a875068ffccf54632ba32f1ee99498ed6</anchor>
      <arglist>(const sf::Rect&lt; float &gt; &amp;of_this)</arglist>
    </member>
    <member kind="function">
      <type>sf::Color</type>
      <name>getColor</name>
      <anchorfile>namespaceutils.html</anchorfile>
      <anchor>ad630ef21f4bca1ad788b01ab5b1c576a</anchor>
      <arglist>(std::string rgb)</arglist>
    </member>
    <member kind="function">
      <type>HSV</type>
      <name>getColorHSV</name>
      <anchorfile>namespaceutils.html</anchorfile>
      <anchor>ac261c84ffe976e984c9e8f6250554514</anchor>
      <arglist>(std::string hsv)</arglist>
    </member>
    <member kind="function">
      <type>sf::Color</type>
      <name>loadPlayerColor</name>
      <anchorfile>namespaceutils.html</anchorfile>
      <anchor>a9322ecfce45674d30353a8155989c3d0</anchor>
      <arglist>(int player_index)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Player.h</name>
    <path>/home/jero/projects/proyecto_final/oop-project/</path>
    <filename>Player_8h.html</filename>
    <includes id="Entity_8h" name="Entity.h" local="yes" imported="no">Entity.h</includes>
    <includes id="Controls_8h" name="Controls.h" local="yes" imported="no">Controls.h</includes>
    <includes id="Weapon_8h" name="Weapon.h" local="yes" imported="no">Weapon.h</includes>
    <includes id="Revolver_8h" name="Revolver.h" local="yes" imported="no">Revolver.h</includes>
    <includes id="Item_8h" name="Item.h" local="yes" imported="no">Item.h</includes>
    <class kind="class">Player</class>
  </compound>
  <compound kind="file">
    <name>Revolver.h</name>
    <path>/home/jero/projects/proyecto_final/oop-project/</path>
    <filename>Revolver_8h.html</filename>
    <includes id="Weapon_8h" name="Weapon.h" local="yes" imported="no">Weapon.h</includes>
    <class kind="class">Revolver</class>
  </compound>
  <compound kind="file">
    <name>Scene.h</name>
    <path>/home/jero/projects/proyecto_final/oop-project/</path>
    <filename>Scene_8h.html</filename>
    <class kind="class">Escena</class>
  </compound>
  <compound kind="file">
    <name>Settings.h</name>
    <path>/home/jero/projects/proyecto_final/oop-project/</path>
    <filename>Settings_8h.html</filename>
    <includes id="Controls_8h" name="Controls.h" local="yes" imported="no">Controls.h</includes>
    <class kind="class">Settings</class>
  </compound>
  <compound kind="file">
    <name>Weapon.h</name>
    <path>/home/jero/projects/proyecto_final/oop-project/</path>
    <filename>Weapon_8h.html</filename>
    <includes id="Entity_8h" name="Entity.h" local="yes" imported="no">Entity.h</includes>
    <class kind="class">Weapon</class>
  </compound>
  <compound kind="file">
    <name>World.h</name>
    <path>/home/jero/projects/proyecto_final/oop-project/</path>
    <filename>World_8h.html</filename>
    <includes id="Settings_8h" name="Settings.h" local="yes" imported="no">Settings.h</includes>
    <includes id="Player_8h" name="Player.h" local="yes" imported="no">Player.h</includes>
    <class kind="class">World</class>
  </compound>
  <compound kind="class">
    <name>Controls</name>
    <filename>classControls.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>KeyState</name>
      <anchorfile>classControls.html</anchorfile>
      <anchor>a3368a8cc7f48800d1d7a96de69414a45</anchor>
      <arglist>(std::string const &amp;key_functionconst)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>BindKey</name>
      <anchorfile>classControls.html</anchorfile>
      <anchor>a19bc69e9e404c5ed5ace023db952da48</anchor>
      <arglist>(std::string const &amp;key_function, sf::Keyboard::Key new_key)</arglist>
    </member>
    <member kind="function">
      <type>sf::Keyboard::Key</type>
      <name>StringToKey</name>
      <anchorfile>classControls.html</anchorfile>
      <anchor>a48dbee594907a90bcb960441bef950dc</anchor>
      <arglist>(std::string const &amp;str_key)</arglist>
    </member>
    <member kind="function">
      <type>sf::Keyboard::Key</type>
      <name>operator&lt;</name>
      <anchorfile>classControls.html</anchorfile>
      <anchor>aa80ef84625130d469b92c88838a02b17</anchor>
      <arglist>(std::string const &amp;str_key)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator[]</name>
      <anchorfile>classControls.html</anchorfile>
      <anchor>a82bc0a8fcb7046b96b11b332ae050f5b</anchor>
      <arglist>(std::string const &amp;key_function)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Controls</name>
      <anchorfile>classControls.html</anchorfile>
      <anchor>ab5b60bab4aa848f8bdd77694d6e81491</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Entity</name>
    <filename>classEntity.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>Update</name>
      <anchorfile>classEntity.html</anchorfile>
      <anchor>aa9ee05393626060907a710597103ad43</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>Draw</name>
      <anchorfile>classEntity.html</anchorfile>
      <anchor>acba770ce4ad65d71fe59561809f788d4</anchor>
      <arglist>(sf::RenderWindow &amp;win)=0</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetKeyword</name>
      <anchorfile>classEntity.html</anchorfile>
      <anchor>a28c7a5abf246f530979ac24fa7474be9</anchor>
      <arglist>(std::string new_key)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>CollidesWith</name>
      <anchorfile>classEntity.html</anchorfile>
      <anchor>a736a5420f57d682bbb2266e4791b449a</anchor>
      <arglist>(const Entity &amp;another)</arglist>
    </member>
    <member kind="function">
      <type>sf::Sprite &amp;</type>
      <name>GetSprite</name>
      <anchorfile>classEntity.html</anchorfile>
      <anchor>a2dc8622060a68391c2817428210bccb1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>sf::Vector2f &amp;</type>
      <name>GetSpeed</name>
      <anchorfile>classEntity.html</anchorfile>
      <anchor>af7d3a5083fac439d9bec950a828d93f5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Entity</name>
      <anchorfile>classEntity.html</anchorfile>
      <anchor>aed643a24c420d3d256d977a8cfc919eb</anchor>
      <arglist>(std::string keyword)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Entity</name>
      <anchorfile>classEntity.html</anchorfile>
      <anchor>a588098978eea6a3486b7361605ff3f0f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>LoadTextures</name>
      <anchorfile>classEntity.html</anchorfile>
      <anchor>a797fe71dce2c965a0bb355ffdb6d0d6f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::string</type>
      <name>m_key</name>
      <anchorfile>classEntity.html</anchorfile>
      <anchor>af8b428b47f16bb7dadde7f7d39f40d3b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>sf::Vector2f</type>
      <name>m_speed</name>
      <anchorfile>classEntity.html</anchorfile>
      <anchor>a7ef487737491b48eacf80c5b271212b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>float</type>
      <name>m_topspeed</name>
      <anchorfile>classEntity.html</anchorfile>
      <anchor>a07367acf03a201bee540ccca423b68aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; sf::Texture &gt;</type>
      <name>m_textures</name>
      <anchorfile>classEntity.html</anchorfile>
      <anchor>ac85b953b52d273b5e23c1bb945f08a26</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>sf::Sprite</type>
      <name>m_sprite</name>
      <anchorfile>classEntity.html</anchorfile>
      <anchor>a349c6abf10608375164c13b3c39c6fb3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Escena</name>
    <filename>classEscena.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>Update</name>
      <anchorfile>classEscena.html</anchorfile>
      <anchor>a83a504829c3088cfae0cf8dc63da386c</anchor>
      <arglist>(Game &amp;g)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>Draw</name>
      <anchorfile>classEscena.html</anchorfile>
      <anchor>ad8534da60a726f988aacb203b974307b</anchor>
      <arglist>(sf::RenderWindow &amp;win)=0</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Escena</name>
      <anchorfile>classEscena.html</anchorfile>
      <anchor>a9fd4e0a58405e5ac6a6fb951612d7ec2</anchor>
      <arglist>(float width, float height)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Escena</name>
      <anchorfile>classEscena.html</anchorfile>
      <anchor>a9dafb05b7100c6652b430684f68d37ce</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>float</type>
      <name>win_width</name>
      <anchorfile>classEscena.html</anchorfile>
      <anchor>a676f9553d75ad9dc456193a8e1762be5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>float</type>
      <name>win_height</name>
      <anchorfile>classEscena.html</anchorfile>
      <anchor>a19635ae40c37a0e9c54ece6ad595afb1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Game</name>
    <filename>classGame.html</filename>
    <member kind="function">
      <type>void</type>
      <name>Run</name>
      <anchorfile>classGame.html</anchorfile>
      <anchor>a96341ca5b54d90adc3ecb3bf0bcd2312</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ProcessEvents</name>
      <anchorfile>classGame.html</anchorfile>
      <anchor>ae7e28abc55af4902c9c39899708d08d7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Update</name>
      <anchorfile>classGame.html</anchorfile>
      <anchor>a1c5373c68261c54aff03e6abe40fee52</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Draw</name>
      <anchorfile>classGame.html</anchorfile>
      <anchor>aad2c20e2c5529244095c50c238911e30</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetScene</name>
      <anchorfile>classGame.html</anchorfile>
      <anchor>aa8e1814aaecc0d9fbdf2af9f361ecfa4</anchor>
      <arglist>(Escena *new_scene)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Close</name>
      <anchorfile>classGame.html</anchorfile>
      <anchor>a5c877aa873414d3c1c75fd371b604216</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Game</name>
      <anchorfile>classGame.html</anchorfile>
      <anchor>a8d1e5232a0399ed59ab025bb5d4e9dbd</anchor>
      <arglist>(float width, float height, std::string window_name)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Game</name>
      <anchorfile>classGame.html</anchorfile>
      <anchor>ae3d112ca6e0e55150d2fdbc704474530</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>utils::HSV</name>
    <filename>classutils_1_1HSV.html</filename>
    <member kind="function">
      <type></type>
      <name>HSV</name>
      <anchorfile>classutils_1_1HSV.html</anchorfile>
      <anchor>a7594e3f0c296fe90932bc8f456025823</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>HSV</name>
      <anchorfile>classutils_1_1HSV.html</anchorfile>
      <anchor>a22149bf9803b26193eddded1483d790e</anchor>
      <arglist>(const sf::Color &amp;rgb)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>HSV</name>
      <anchorfile>classutils_1_1HSV.html</anchorfile>
      <anchor>a7286c1bdb8d0bed8f3656cc9fa371dd8</anchor>
      <arglist>(float hue, float sat, float value)</arglist>
    </member>
    <member kind="function">
      <type>sf::Color</type>
      <name>MakeRGB</name>
      <anchorfile>classutils_1_1HSV.html</anchorfile>
      <anchor>a178e762801057fcf2bf36e5ffb535289</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetHue</name>
      <anchorfile>classutils_1_1HSV.html</anchorfile>
      <anchor>af9a49d0c055d9263c8b82895533b8e75</anchor>
      <arglist>(float hue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetSat</name>
      <anchorfile>classutils_1_1HSV.html</anchorfile>
      <anchor>aade07d2859eb8734679fc500309c60cf</anchor>
      <arglist>(float sat)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetVal</name>
      <anchorfile>classutils_1_1HSV.html</anchorfile>
      <anchor>a83ee902a7ef3a4d9f52b96708eb33448</anchor>
      <arglist>(float val)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetHue</name>
      <anchorfile>classutils_1_1HSV.html</anchorfile>
      <anchor>a4fb4b3739f8ddb98e9110bcec4316356</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetSat</name>
      <anchorfile>classutils_1_1HSV.html</anchorfile>
      <anchor>a127e634e3d32cc12d16380acb605569f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetVal</name>
      <anchorfile>classutils_1_1HSV.html</anchorfile>
      <anchor>a618f268a57e8ba013a227780c64284f2</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Item</name>
    <filename>classItem.html</filename>
    <base>Entity</base>
    <member kind="function">
      <type></type>
      <name>Item</name>
      <anchorfile>classItem.html</anchorfile>
      <anchor>a297720c02984eab37332ae795d22189d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Update</name>
      <anchorfile>classItem.html</anchorfile>
      <anchor>a93dd04b3c6bd57e9bf255abc2dfd70a5</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Draw</name>
      <anchorfile>classItem.html</anchorfile>
      <anchor>a16267102b31d6b814f555a71a1940ea5</anchor>
      <arglist>(sf::RenderWindow &amp;win) override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Match</name>
    <filename>classMatch.html</filename>
    <base>Escena</base>
    <member kind="function">
      <type>void</type>
      <name>Update</name>
      <anchorfile>classMatch.html</anchorfile>
      <anchor>ace273e7631fcd71622a0d7af2f37a32d</anchor>
      <arglist>(Game &amp;g)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Draw</name>
      <anchorfile>classMatch.html</anchorfile>
      <anchor>abaa3f1bdfc512ad372359e88b23a03c8</anchor>
      <arglist>(sf::RenderWindow &amp;win)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Match</name>
      <anchorfile>classMatch.html</anchorfile>
      <anchor>a6ffbe5a713f37ce3e1decb207215d7f6</anchor>
      <arglist>(float width, float height)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Match</name>
      <anchorfile>classMatch.html</anchorfile>
      <anchor>a4cbfcaff4f14e7411242423f19c28153</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Menu</name>
    <filename>classMenu.html</filename>
    <base>Escena</base>
    <member kind="function">
      <type>void</type>
      <name>Update</name>
      <anchorfile>classMenu.html</anchorfile>
      <anchor>a693fada95d90ef79c172d754968afa3a</anchor>
      <arglist>(Game &amp;g)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Draw</name>
      <anchorfile>classMenu.html</anchorfile>
      <anchor>af7368aec9f540c9aec22203718a55122</anchor>
      <arglist>(sf::RenderWindow &amp;win)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Menu</name>
      <anchorfile>classMenu.html</anchorfile>
      <anchor>a158fca31749f101c5f05d5d0135c8f50</anchor>
      <arglist>(float width, float height, std::string location=&quot;principal&quot;)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Player</name>
    <filename>classPlayer.html</filename>
    <base>Entity</base>
    <member kind="function">
      <type>void</type>
      <name>Update</name>
      <anchorfile>classPlayer.html</anchorfile>
      <anchor>a5e17be3418fa0ac0192c05efaf3dc8bd</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Draw</name>
      <anchorfile>classPlayer.html</anchorfile>
      <anchor>afd2fe9c2dce1c3a231c6fb3ee40b73cc</anchor>
      <arglist>(sf::RenderWindow &amp;win) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ApplyGravity</name>
      <anchorfile>classPlayer.html</anchorfile>
      <anchor>ac299a18be97af11e6f5ef042b6d4d8f3</anchor>
      <arglist>(float gravity)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ApplyResponse</name>
      <anchorfile>classPlayer.html</anchorfile>
      <anchor>aafe6efb7fc25b0d02a4549cf8b65c113</anchor>
      <arglist>(const sf::Vector2&lt; double &gt; &amp;vec)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetJumpSpeed</name>
      <anchorfile>classPlayer.html</anchorfile>
      <anchor>a708e1e29894da1e1c5ce011b7c9452b8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetIndex</name>
      <anchorfile>classPlayer.html</anchorfile>
      <anchor>ad9a845bd6aa0685dcca80d612a249117</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Player</name>
      <anchorfile>classPlayer.html</anchorfile>
      <anchor>a1e78929df5e1d768207e6d91e642dc5b</anchor>
      <arglist>(float initial_x, float initial_y, int player_index)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Player</name>
      <anchorfile>classPlayer.html</anchorfile>
      <anchor>a749d2c00e1fe0f5c2746f7505a58c062</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Revolver</name>
    <filename>classRevolver.html</filename>
    <base>Weapon</base>
    <member kind="function">
      <type>void</type>
      <name>Update</name>
      <anchorfile>classRevolver.html</anchorfile>
      <anchor>a38bc2dae886f2a6cb665aacacd5f07e2</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Draw</name>
      <anchorfile>classRevolver.html</anchorfile>
      <anchor>a5ebe694d641300839365d80e967589f5</anchor>
      <arglist>(sf::RenderWindow &amp;win) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Attack</name>
      <anchorfile>classRevolver.html</anchorfile>
      <anchor>aeed7f343f944db3188c922d6c48af057</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Revolver</name>
      <anchorfile>classRevolver.html</anchorfile>
      <anchor>a25ee33f7f88e420194800c2de498879e</anchor>
      <arglist>(bool facing, float wdt)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Settings</name>
    <filename>classSettings.html</filename>
    <member kind="function">
      <type>std::string</type>
      <name>GetValue</name>
      <anchorfile>classSettings.html</anchorfile>
      <anchor>aef21d64fa547c2fd8c3db216ec9b121f</anchor>
      <arglist>(std::string const &amp;field) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ChangeValue</name>
      <anchorfile>classSettings.html</anchorfile>
      <anchor>ae9cb34716b0b00528cc20ce94afb8fd7</anchor>
      <arglist>(std::string const &amp;field, std::string const &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>LoadFile</name>
      <anchorfile>classSettings.html</anchorfile>
      <anchor>aae064d9ade9680a81dcc7ecf4cc140c7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>LoadBackUp</name>
      <anchorfile>classSettings.html</anchorfile>
      <anchor>a12e31fec917410ecac81353639455a59</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Reload</name>
      <anchorfile>classSettings.html</anchorfile>
      <anchor>ad49904452450a2e3d6199e16252e7c28</anchor>
      <arglist>(std::string const &amp;FileName, std::string const &amp;KeyWord)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>RestoreAllToDef</name>
      <anchorfile>classSettings.html</anchorfile>
      <anchor>a72e485d6b1b5a51257dd64b80af99c56</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>RestoreThisToDef</name>
      <anchorfile>classSettings.html</anchorfile>
      <anchor>aa57ae4ff70c22481c3427b34b906ea8d</anchor>
      <arglist>(std::string const &amp;field)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SaveChanges</name>
      <anchorfile>classSettings.html</anchorfile>
      <anchor>ab7d180010d76b7575b1571d58eb71fde</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>operator[]</name>
      <anchorfile>classSettings.html</anchorfile>
      <anchor>a568ee1d9540d867c554d9a496628d320</anchor>
      <arglist>(std::string const &amp;field) const</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Settings</name>
      <anchorfile>classSettings.html</anchorfile>
      <anchor>ad244ffbefca47bc602e38af82e704978</anchor>
      <arglist>(std::string const &amp;FileName, std::string const &amp;KeyWord)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Weapon</name>
    <filename>classWeapon.html</filename>
    <base>Entity</base>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>Update</name>
      <anchorfile>classWeapon.html</anchorfile>
      <anchor>a84ee843f84b430a293fd9c6291efc354</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>Draw</name>
      <anchorfile>classWeapon.html</anchorfile>
      <anchor>a514eb9bae8f80526a4c6f122e3f69a08</anchor>
      <arglist>(sf::RenderWindow &amp;win)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>Attack</name>
      <anchorfile>classWeapon.html</anchorfile>
      <anchor>a14279c369ff4281e806002b273ab3e65</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetText</name>
      <anchorfile>classWeapon.html</anchorfile>
      <anchor>af30d03cb858e73d627cbbc65be1a583e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetPos</name>
      <anchorfile>classWeapon.html</anchorfile>
      <anchor>ab2ed4224a34e9ffc038c82d773beee2a</anchor>
      <arglist>(const sf::Vector2f &amp;relative_to, bool facing)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Weapon</name>
      <anchorfile>classWeapon.html</anchorfile>
      <anchor>aea3bab5cece1ee372e6560babb25fdd8</anchor>
      <arglist>(int damage, bool facing, float wdt)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Weapon</name>
      <anchorfile>classWeapon.html</anchorfile>
      <anchor>ac5f7305f5d08c48003c826e6e73f37da</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>sf::Vector2f</type>
      <name>OffSet</name>
      <anchorfile>classWeapon.html</anchorfile>
      <anchor>adbd305fcedc6a90777fc31b501f2e479</anchor>
      <arglist>(const sf::Vector2f &amp;to_offset)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>float</type>
      <name>m_width</name>
      <anchorfile>classWeapon.html</anchorfile>
      <anchor>ab7e966884de2a73893b887d1c8af260e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>m_current</name>
      <anchorfile>classWeapon.html</anchorfile>
      <anchor>a2b6701a5bb8bbaac9fb8e55af3f38cd5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>m_damage</name>
      <anchorfile>classWeapon.html</anchorfile>
      <anchor>ab4eb889c425096057c2888847e7a8a7d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>sf::Vector2f</type>
      <name>m_pos</name>
      <anchorfile>classWeapon.html</anchorfile>
      <anchor>a346f0aa3043922a32ce65bea10862794</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>World</name>
    <filename>classWorld.html</filename>
    <member kind="function">
      <type>void</type>
      <name>Draw</name>
      <anchorfile>classWorld.html</anchorfile>
      <anchor>a9dcafffbf359bedb378b4d7c9935305d</anchor>
      <arglist>(sf::RenderWindow &amp;win)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CollidesWith</name>
      <anchorfile>classWorld.html</anchorfile>
      <anchor>aa5432d6d4f0ae08aaf1a34b2c5450da9</anchor>
      <arglist>(const sf::Sprite &amp;entity, int index=0)</arglist>
    </member>
    <member kind="function">
      <type>sf::Vector2&lt; double &gt;</type>
      <name>GetResponse</name>
      <anchorfile>classWorld.html</anchorfile>
      <anchor>af63b2c6a883eb04484356d4c3911fddc</anchor>
      <arglist>(const sf::Sprite &amp;entity, int index)</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>GetGravity</name>
      <anchorfile>classWorld.html</anchorfile>
      <anchor>ad3d4bb9dbffbd44a7e2f932996d354b3</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetBase</name>
      <anchorfile>classWorld.html</anchorfile>
      <anchor>a61b04362083f5a4848cda63b1474e984</anchor>
      <arglist>(int which) const</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>World</name>
      <anchorfile>classWorld.html</anchorfile>
      <anchor>aafe73f74a4546489c8be899bc396cbf2</anchor>
      <arglist>(float wdt, float hgt, float gravity, std::string map_name=&quot;MAIN&quot;)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>utils</name>
    <filename>namespaceutils.html</filename>
    <class kind="class">utils::HSV</class>
    <member kind="function">
      <type>HSV</type>
      <name>MakeHSV</name>
      <anchorfile>namespaceutils.html</anchorfile>
      <anchor>a74fcd67e4f22f40a83e7dc52f1b1fdbe</anchor>
      <arglist>(const sf::Color &amp;rgb)</arglist>
    </member>
    <member kind="function">
      <type>sf::Vector2f</type>
      <name>getCenter</name>
      <anchorfile>namespaceutils.html</anchorfile>
      <anchor>a875068ffccf54632ba32f1ee99498ed6</anchor>
      <arglist>(const sf::Rect&lt; float &gt; &amp;of_this)</arglist>
    </member>
    <member kind="function">
      <type>sf::Color</type>
      <name>getColor</name>
      <anchorfile>namespaceutils.html</anchorfile>
      <anchor>ad630ef21f4bca1ad788b01ab5b1c576a</anchor>
      <arglist>(std::string rgb)</arglist>
    </member>
    <member kind="function">
      <type>HSV</type>
      <name>getColorHSV</name>
      <anchorfile>namespaceutils.html</anchorfile>
      <anchor>ac261c84ffe976e984c9e8f6250554514</anchor>
      <arglist>(std::string hsv)</arglist>
    </member>
    <member kind="function">
      <type>sf::Color</type>
      <name>loadPlayerColor</name>
      <anchorfile>namespaceutils.html</anchorfile>
      <anchor>a9322ecfce45674d30353a8155989c3d0</anchor>
      <arglist>(int player_index)</arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>Final Project for OOP: LOVIGAME</title>
    <filename>index.html</filename>
    <docanchor file="index.html" title="Introduction">intro_sec</docanchor>
    <docanchor file="index.html" title="Authors:">authors</docanchor>
  </compound>
</tagfile>
