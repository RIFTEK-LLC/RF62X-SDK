<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="16008000">
	<Item Name="My Computer" Type="My Computer">
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="Call dotNET DLL_LV2012_NI Verified.vi" Type="VI" URL="../Call dotNET DLL_LV2012_NI Verified.vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="mscorlib" Type="VI" URL="mscorlib">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="rf62Xsdk.dll" Type="Document" URL="../rf62Xsdk.dll"/>
		</Item>
		<Item Name="Build Specifications" Type="Build">
			<Item Name="Call dotNET DLL_LV2012_NI Verified" Type="EXE">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{3853D205-76F2-4321-BC8A-6F3CAE7CC0D4}</Property>
				<Property Name="App_INI_GUID" Type="Str">{74EEDF00-C336-4696-9937-BD4EA6D1B5AA}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="Bld_autoIncrement" Type="Bool">true</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{4D253180-40A6-45BE-B745-166D8A5BD8CF}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">Call dotNET DLL_LV2012_NI Verified</Property>
				<Property Name="Bld_excludeInlineSubVIs" Type="Bool">true</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../builds/NI_AB_PROJECTNAME/Call dotNET DLL_LV2012_NI Verified</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToCommon</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{2EC0EB95-76E1-4982-8CB9-C5FFD2381211}</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">Application.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../builds/NI_AB_PROJECTNAME/Call dotNET DLL_LV2012_NI Verified/Application.exe</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../builds/NI_AB_PROJECTNAME/Call dotNET DLL_LV2012_NI Verified/data</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Source[0].itemID" Type="Str">{EC98E581-BF88-40D7-B9FD-4C3A3474D7C7}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/Call dotNET DLL_LV2012_NI Verified.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">2</Property>
				<Property Name="TgtF_companyName" Type="Str">Reference Image</Property>
				<Property Name="TgtF_fileDescription" Type="Str">Call dotNET DLL_LV2012_NI Verified</Property>
				<Property Name="TgtF_internalName" Type="Str">Call dotNET DLL_LV2012_NI Verified</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">Copyright © 2020 Reference Image</Property>
				<Property Name="TgtF_productName" Type="Str">Call dotNET DLL_LV2012_NI Verified</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{6C27E2CC-C459-4CC7-9814-F3724E8F35D5}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">Application.exe</Property>
			</Item>
			<Item Name="Call dotNET DLL_LV2012_NI Verified2" Type="EXE">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{284AA171-32DB-437C-96C4-3CDD1EBC02B0}</Property>
				<Property Name="App_INI_GUID" Type="Str">{8E85F227-7692-4234-9B69-8D0107183DB5}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="Bld_autoIncrement" Type="Bool">true</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{2C1BBCE3-F327-418B-B345-6F141D1E2270}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">Call dotNET DLL_LV2012_NI Verified2</Property>
				<Property Name="Bld_excludeInlineSubVIs" Type="Bool">true</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../builds/NI_AB_PROJECTNAME/Call dotNET DLL_LV2012_NI Verified2</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToCommon</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{432E331A-E656-4F0C-9F22-91034816B935}</Property>
				<Property Name="Bld_version.build" Type="Int">1</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">Application.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../builds/NI_AB_PROJECTNAME/Call dotNET DLL_LV2012_NI Verified2/Application.exe</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../builds/NI_AB_PROJECTNAME/Call dotNET DLL_LV2012_NI Verified2/data</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Source[0].itemID" Type="Str">{1964A0E8-1A6E-4460-B2B2-E2F26C58DE8B}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/Call dotNET DLL_LV2012_NI Verified.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">2</Property>
				<Property Name="TgtF_companyName" Type="Str">Reference Image</Property>
				<Property Name="TgtF_fileDescription" Type="Str">Call dotNET DLL_LV2012_NI Verified2</Property>
				<Property Name="TgtF_internalName" Type="Str">Call dotNET DLL_LV2012_NI Verified2</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">Copyright © 2020 Reference Image</Property>
				<Property Name="TgtF_productName" Type="Str">Call dotNET DLL_LV2012_NI Verified2</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{74F437E3-CF7C-45F2-8BF2-C36E0B364AA4}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">Application.exe</Property>
			</Item>
			<Item Name="Call dotNET DLL_LV2012_NI Verified3" Type="EXE">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{299D269A-0F96-464B-866C-4A2164CE9B7B}</Property>
				<Property Name="App_INI_GUID" Type="Str">{FDF161DA-FF3D-4908-8DDA-4D42012085C3}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="Bld_autoIncrement" Type="Bool">true</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{9FF14B79-973B-47D8-94EC-BF7653733320}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">Call dotNET DLL_LV2012_NI Verified3</Property>
				<Property Name="Bld_excludeInlineSubVIs" Type="Bool">true</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../builds/NI_AB_PROJECTNAME/Call dotNET DLL_LV2012_NI Verified3</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToCommon</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{C8FC69B6-1DC5-4C33-8EFF-69B7C3972D77}</Property>
				<Property Name="Bld_version.build" Type="Int">1</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">Application.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../builds/NI_AB_PROJECTNAME/Call dotNET DLL_LV2012_NI Verified3/Application.exe</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../builds/NI_AB_PROJECTNAME/Call dotNET DLL_LV2012_NI Verified3/data</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Source[0].itemID" Type="Str">{1964A0E8-1A6E-4460-B2B2-E2F26C58DE8B}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/Call dotNET DLL_LV2012_NI Verified.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">2</Property>
				<Property Name="TgtF_companyName" Type="Str">Reference Image</Property>
				<Property Name="TgtF_fileDescription" Type="Str">Call dotNET DLL_LV2012_NI Verified3</Property>
				<Property Name="TgtF_internalName" Type="Str">Call dotNET DLL_LV2012_NI Verified3</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">Copyright © 2020 Reference Image</Property>
				<Property Name="TgtF_productName" Type="Str">Call dotNET DLL_LV2012_NI Verified3</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{F2175C77-F476-4512-817A-A8162969CA77}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">Application.exe</Property>
			</Item>
			<Item Name="Call dotNET DLL_LV2012_NI Verified4" Type="EXE">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{A9566ADE-DDD1-4970-B7E1-86CDE6453E50}</Property>
				<Property Name="App_INI_GUID" Type="Str">{45030731-7B28-4565-9975-C4145A21DA87}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="Bld_autoIncrement" Type="Bool">true</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{AE55BDCE-C492-4AD2-B6C9-658CDBBCC26B}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">Call dotNET DLL_LV2012_NI Verified4</Property>
				<Property Name="Bld_excludeInlineSubVIs" Type="Bool">true</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../builds/NI_AB_PROJECTNAME/Call dotNET DLL_LV2012_NI Verified4</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToCommon</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{EFC8D3D3-4547-425F-B36D-3E56F2045C7B}</Property>
				<Property Name="Bld_version.build" Type="Int">1</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">Application.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../builds/NI_AB_PROJECTNAME/Call dotNET DLL_LV2012_NI Verified4/Application.exe</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../builds/NI_AB_PROJECTNAME/Call dotNET DLL_LV2012_NI Verified4/data</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Source[0].itemID" Type="Str">{1964A0E8-1A6E-4460-B2B2-E2F26C58DE8B}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/Call dotNET DLL_LV2012_NI Verified.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">2</Property>
				<Property Name="TgtF_companyName" Type="Str">Reference Image</Property>
				<Property Name="TgtF_fileDescription" Type="Str">Call dotNET DLL_LV2012_NI Verified4</Property>
				<Property Name="TgtF_internalName" Type="Str">Call dotNET DLL_LV2012_NI Verified4</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">Copyright © 2020 Reference Image</Property>
				<Property Name="TgtF_productName" Type="Str">Call dotNET DLL_LV2012_NI Verified4</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{95C80055-4978-4006-B047-5A2AEED21076}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">Application.exe</Property>
			</Item>
			<Item Name="Call dotNET DLL_LV2012_NI Verified5" Type="EXE">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{0C4B22A4-CAB9-4668-84F4-527936EF2C5A}</Property>
				<Property Name="App_INI_GUID" Type="Str">{FF5B005C-65C8-4D3E-A5E0-5FFA4A0C54D8}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="Bld_autoIncrement" Type="Bool">true</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{65DCA565-B468-4F2B-B24B-93EE6FE9A8B2}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">Call dotNET DLL_LV2012_NI Verified5</Property>
				<Property Name="Bld_excludeInlineSubVIs" Type="Bool">true</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../builds/NI_AB_PROJECTNAME/Call dotNET DLL_LV2012_NI Verified5</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToCommon</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{09D37269-73DB-47C5-B2F8-EFAD66F53E53}</Property>
				<Property Name="Bld_version.build" Type="Int">1</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">Application.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../builds/NI_AB_PROJECTNAME/Call dotNET DLL_LV2012_NI Verified5/Application.exe</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../builds/NI_AB_PROJECTNAME/Call dotNET DLL_LV2012_NI Verified5/data</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Source[0].itemID" Type="Str">{1964A0E8-1A6E-4460-B2B2-E2F26C58DE8B}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/Call dotNET DLL_LV2012_NI Verified.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">2</Property>
				<Property Name="TgtF_companyName" Type="Str">Reference Image</Property>
				<Property Name="TgtF_fileDescription" Type="Str">Call dotNET DLL_LV2012_NI Verified5</Property>
				<Property Name="TgtF_internalName" Type="Str">Call dotNET DLL_LV2012_NI Verified5</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">Copyright © 2020 Reference Image</Property>
				<Property Name="TgtF_productName" Type="Str">Call dotNET DLL_LV2012_NI Verified5</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{44F321DE-ED30-41CC-B8CD-9E9A1EB1D225}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">Application.exe</Property>
			</Item>
		</Item>
	</Item>
</Project>
