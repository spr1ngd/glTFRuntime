
- 迁移至自己的仓库和源码版本容易做一个合并
git : https://github.com/spr1ngd/glTFRuntime.git

- 拓展的代码放在EXT中，避免过渡修改源码产生后期不好合并的情况
    - 修改源码部分最好是以拓展接口的形式独立给出，不要修改原有内容
- 添加 StaticMeshConfig.LoadStaticMeshTransform

- 需要在glTFRuntime内部做一个缓冲机制，直接缓冲StaticMesh,Texture等数据  (js中调用httprequest只是缓冲源文件，避免重复加载，无法影响到glTF)