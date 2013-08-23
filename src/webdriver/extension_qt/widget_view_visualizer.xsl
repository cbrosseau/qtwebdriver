<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:template match="/element()">
    <html>
      <head>
        <title><xsl:value-of select="@name"/></title>
      </head>
      <body>
        <xsl:apply-templates/>
      </body>
    </html>
  </xsl:template>

  <xsl:template match="QCheckBox">
    <input type="checkbox">
      <xsl:call-template name="style"/>
      <xsl:value-of select="@text"/>
    </input>
  </xsl:template>
  <xsl:template match="QLabel">
    <span>
      <xsl:call-template name="style"/>
      <xsl:value-of select="@text"/>
    </span>
  </xsl:template>
  <xsl:template match="QLineEdit">
    <input type="text">
      <xsl:call-template name="style"/>
    </input>
  </xsl:template>
  <xsl:template match="QPushButton">
    <input type="submit">
      <xsl:call-template name="style"/>
      <xsl:attribute name="value" select="@text"/>
    </input>
  </xsl:template>
  <xsl:template match="QScrollArea">
    <div>
      <xsl:call-template name="style"/>
      <xsl:apply-templates/>
    </div>
  </xsl:template>

  <xsl:template name="style">
    <xsl:attribute name="style">
      <xsl:if test="@width">
        width:<xsl:value-of select="@width"/>;
      </xsl:if>
      <xsl:if test="@height">
        height:<xsl:value-of select="@height"/>;
      </xsl:if>
    </xsl:attribute>
  </xsl:template>
</xsl:stylesheet>
