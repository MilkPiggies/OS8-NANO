
scan:
do {
    uint32_t lba = g_RootDirectoryEnd + (currentCluster - 2) * g_BootSector.SectorPerCluster;
    ok = ok && readSectors(disk, lba, g_BootSector.SectorPerCluster, outputBuffer);
    outputBuffer += g_BootSector.SectorsPerCluster * g_BootSector.BytesPerSector;