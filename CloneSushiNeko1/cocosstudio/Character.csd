<GameFile>
  <PropertyGroup Name="Character" Type="Node" ID="4b04edc5-bc22-4621-ae73-f4e75e96ca98" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="4" Speed="0.5000" ActivedAnimationName="chop">
        <Timeline ActionTag="172125716" Property="Position">
          <PointFrame FrameIndex="1" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="2" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="172125716" Property="FileData">
          <TextureFrame FrameIndex="1" Tween="False">
            <TextureFile Type="Normal" Path="Assets/Images/resources-2x/character1.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="2" Tween="False">
            <TextureFile Type="Normal" Path="Assets/Images/resources-2x/character2.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="3" Tween="False">
            <TextureFile Type="Normal" Path="Assets/Images/resources-2x/character3.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="4" Tween="False">
            <TextureFile Type="Normal" Path="Assets/Images/resources-2x/character2.png" Plist="" />
          </TextureFrame>
        </Timeline>
        <Timeline ActionTag="172125716" Property="AnchorPoint">
          <ScaleFrame FrameIndex="1" X="1.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="2" X="1.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="default" StartIndex="0" EndIndex="0">
          <RenderColor A="150" R="255" G="105" B="180" />
        </AnimationInfo>
        <AnimationInfo Name="chop" StartIndex="1" EndIndex="6">
          <RenderColor A="150" R="65" G="105" B="225" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" CustomClassName="Character" Tag="5" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Cat" ActionTag="172125716" Tag="35" IconVisible="False" LeftMargin="-365.0000" TopMargin="-217.0000" ctype="SpriteObjectData">
            <Size X="365.0000" Y="217.0000" />
            <AnchorPoint ScaleX="1.0000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="Assets/Images/resources-2x/character1.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>