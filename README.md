映像情報特論　修士１年履修　yuv画像処理プログラム
=============================
環境：xcode  
言語：c言語  
コンパイラによって、乱数の生成などが異なったりするので、実行する場合は要確認しておくこと.  
また、YUVファイルにはヘッダ情報が無いので、注意すること。つまり、画像の縦横などの情報をプログラムに付与する必要性がある.  
処理を施した出力ファイル、施す入力ファイルは未アップ.  
Author : 栢割　隆之  
Twitter : @kayataka1507  
-------------------------  
<ol>
<<<<<<< HEAD
  <li>edge_imgCopy</li>
  <p>単純な画像コピー。縦横比を２倍にしている。</p>

  <li>edge_only</li>
  <p>縦横に対するエッジ処理</p>
  
  <li>edge_k3</li>
  <p>エッジ処理。kの値により、精鋭化の具合が変化。</p>
  
  <li>edge_ver_hor</li>
  <p>水平方向のみのエッジ処理</p>
  
  <li>edge_video</li>
  <p>yuvビデオ（動画）ファイルエッジ処理</p>
  
  <li>noise_copy</li>
  <p>ノイズ処理？</p>
  
  <li>noise_video</li>
  <p>ノイズ処理？（動画）</p>
  
  <li>output_yuv_files</li>
  <p>処理を施した後の出力ファイル</p>
  
  <li>yuv_files</li>
  <p>処理を施す入力ファイル</p>
</ol>

